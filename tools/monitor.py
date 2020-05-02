#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Data Monitor

Requirement:

    ```
    pip install pyserial
    pip install PyQt5
    # or `pip install PySide2`. PySide 2 does't work with Python 3.8.0
    pip install https://github.com/pyqtgraph/pyqtgraph/archive/develop.zip
    ```
"""

from datetime import datetime
import traceback
import sys
import serial
from serial.tools import list_ports
import numpy as np
import pyqtgraph as pg
import pyqtgraph.exporters


# using baudrate to configure voltmeter
amp = 0     # select AMP, 0: β=1.449, range: [5mA, 950mA] 1: β=119.52, range: [50uA, 11mA]
div = 11    # min = 11, sample rate = 48 MHz / div / 2 / 11, each channel takes 11 clock, 2 channels
baudrate = 0x40000000 | (div << 16) | (amp << 8)
sample_rate = 48000000 / div / 2 / 11
beta = (1.449, 119.52)[amp]

MAX_HISTORY = 1 << 24


class Probe(pg.QtCore.QThread):
    error = pg.QtCore.Signal(int)

    def __init__(self):
        super().__init__()
        self.done = False
        self.data = np.empty((4, 1 << 16))
        self.index = 0
        self.n = 0

    def run(self):
        for p in list_ports.comports():
            print(p)
            if p[2].upper().startswith('USB VID:PID=0D28:0204'):
                port = p[0]
                break
        else:
            print('No device found')
            self.error.emit(1)
            return

        print('Open {}'.format(port))
        device = serial.Serial(port=port,
                               baudrate=baudrate,
                               bytesize=8,
                               parity='N',
                               stopbits=1,
                               timeout=1)

        for _ in range(1024):
            device.read(4)

        # output = datetime.now().strftime('data-%Y%m%d-%H%M%S.csv')
        output = 'data.csv'
        with open(output, 'w') as f:
            f.write('t,I,U\n')
            while not self.done:
                try:
                    raw = device.read(4)
                    current = (raw[3] << 2) | (raw[2] >> 6)
                    current = current * 1.3524 / beta
                    voltage = ((raw[2] & 0x3F) << 4) | (raw[1] >> 4)
                    samples = ((raw[1] & 0xF) << 8) | raw[0]
                    if self.index & 0xFFF == 0:
                        print([samples, current, voltage])
                    self.n += samples
                    self.data[0][self.index] = self.n / sample_rate
                    self.data[1][self.index] = self.n
                    self.data[2][self.index] = current
                    self.data[3][self.index] = voltage
                    self.index += 1
                    if self.index >= self.data.shape[1]:
                        if self.index < MAX_HISTORY:
                            buffer = np.concatenate(
                                (self.data, np.empty(self.data.shape)), axis=1)
                            self.data = buffer
                        else:
                            half = MAX_HISTORY >> 1
                            np.savetxt(f, self.data[1:,:half].T, ['%d', '%f', '%d'], ',')
                            self.data[:,:half] = self.data[:,half:]
                            self.index -= half
                except IOError:
                    traceback.print_exc()
                    self.error.emit(2)
                    break
                except ValueError:
                    print(raw)
                    traceback.print_exc()

            np.savetxt(f, self.data[1:,:self.index].T, ['%d', '%f', '%d'], ',')
            device.close()

    def get(self):
        return self.data, self.index

    def start(self):
        self.done = False
        super().start()

    def close(self):
        self.done = True
        self.wait(2)


class MainWindow(pg.QtGui.QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowIcon(self.style().standardIcon(pg.QtGui.QStyle.SP_MediaSeekForward))
        self.setWindowTitle('Data Monitor')
        self.resize(1200, 720)
        self.widget = pg.PlotWidget()
        self.setCentralWidget(self.widget)

        self.widget.setLabel('left', 'I')
        self.widget.setLabel('bottom', 't/s')
        self.widget.showButtons()
        self.widget.setXRange(0, 10.0)
        self.widget.setYRange(0, 1024)
        # self.widget.setLimits(minYRange=0, maxYRange=1024, yMin=0, yMax=1024)
        self.widget.setMouseEnabled(True, False)
        # self.widget.setAutoPan(x=True)
        # self.widget.enableAutoRange(x=True)
        line = pg.InfiniteLine(
            pos=512, angle=0, movable=True, bounds=[0, 1024])
        self.widget.addItem(line)
        self.widget.showGrid(x=True, y=True, alpha=0.5)
        self.plot = self.widget.plot()
        self.plot.setPen((0, 255, 0))

        self.toolbar = self.addToolBar('toolbar')
        self.toolbar.setMovable(False)

        pauseAction = pg.QtGui.QAction('▶️', self)
        pauseAction.setToolTip('Start/Stop(Space)')
        pauseAction.setShortcut(' ')
        pauseAction.setCheckable(True)
        pauseAction.setChecked(True)
        pauseAction.toggled.connect(self.pause)
        self.toolbar.addAction(pauseAction)

        saveAction = pg.QtGui.QAction('💾', self)
        saveAction.setToolTip('Save(Ctrl+S)')
        saveAction.setShortcut('Ctrl+S')
        saveAction.triggered.connect(self.save)
        self.toolbar.addAction(saveAction)

        '🔍🔎⇆↔⇅↕'
        xZoomInAction = pg.QtGui.QAction('🔍⇆', self)
        xZoomInAction.setToolTip('X Zoom In([)')
        xZoomInAction.setShortcut('[')
        xZoomInAction.triggered.connect(self.zoomInX)
        self.toolbar.addAction(xZoomInAction)

        xZoomOutAction = pg.QtGui.QAction('🔍↔', self)
        xZoomOutAction.setToolTip('X Zoom Out(])')
        xZoomOutAction.setShortcut(']')
        xZoomOutAction.triggered.connect(self.zoomOutX)
        self.toolbar.addAction(xZoomOutAction)

        yZoomInAction = pg.QtGui.QAction('🔍⇅', self)
        yZoomInAction.setToolTip('Y Zoom In(-)')
        yZoomInAction.setShortcut('-')
        yZoomInAction.triggered.connect(self.zoomInY)
        self.toolbar.addAction(yZoomInAction)

        yZoomOutAction = pg.QtGui.QAction('🔍↕', self)
        yZoomOutAction.setToolTip('Y Zoom Out(+)')
        yZoomOutAction.setShortcut('=')
        yZoomOutAction.triggered.connect(self.zoomOutY)
        self.toolbar.addAction(yZoomOutAction)

        '🡸🡹🡺🡻🢀🢁🢂🢃🡰🡱🡲🡳🠈🠉🠊🠋←↑→↓⇇⇈⇉⇊⇦⇧⇨⇩⇐⇑⇒⇓⬇⬆➡⬅'
        leftAction = pg.QtGui.QAction('←', self)
        # leftAction.setIcon(self.style().standardIcon(pg.QtGui.QStyle.SP_ArrowLeft))
        leftAction.setShortcut(pg.QtGui.QKeySequence(pg.QtCore.Qt.Key_Left))
        leftAction.triggered.connect(self.moveLeft)
        self.toolbar.addAction(leftAction)

        rightAction = pg.QtGui.QAction('→', self)
        # rightAction.setIcon(self.style().standardIcon(pg.QtGui.QStyle.SP_ArrowRight))
        rightAction.setShortcut(pg.QtGui.QKeySequence(pg.QtCore.Qt.Key_Right))
        rightAction.triggered.connect(self.moveRight)
        self.toolbar.addAction(rightAction)

        upAction = pg.QtGui.QAction('↑', self)
        # upAction.setIcon(self.style().standardIcon(pg.QtGui.QStyle.SP_ArrowUp))
        upAction.setShortcut(pg.QtGui.QKeySequence(pg.QtCore.Qt.Key_Up))
        upAction.triggered.connect(self.moveUp)
        self.toolbar.addAction(upAction)

        downAction = pg.QtGui.QAction('↓', self)
        # downAction.setIcon(self.style().standardIcon(pg.QtGui.QStyle.SP_ArrowDown))
        downAction.setShortcut(pg.QtGui.QKeySequence(pg.QtCore.Qt.Key_Down))
        downAction.triggered.connect(self.moveDown)
        self.toolbar.addAction(downAction)

        pinAction = pg.QtGui.QAction('📌', self)
        pinAction.setShortcut('Ctrl+T')
        pinAction.setCheckable(True)
        pinAction.setChecked(False)
        pinAction.toggled.connect(self.pin)
        self.toolbar.addAction(pinAction)

        infoAction = pg.QtGui.QAction('💡', self)
        infoAction.setShortcut('Shift+/')
        infoAction.triggered.connect(self.showInfo)
        self.toolbar.addAction(infoAction)

        # comboBox = pg.QtGui.QComboBox()
        # self.toolbar.addWidget(comboBox)

        self.toolbar.setStyleSheet(
            "QToolButton:!hover {color: rgb(0,255,0); background-color: transparent}"
            "QToolButton:checked {color: rgb(30, 30, 30); background-color: rgb(0,255,0)}"
            "QToolBar {background: rgb(30, 30, 30); border: none}")

        self.freeze = False
        self.probe = Probe()
        self.probe.error.connect(self.handle_error)
        self.probe.start()
        self.timer = pg.QtCore.QTimer()
        self.timer.timeout.connect(self.update)
        self.timer.start(50)

    def update(self):
        if not self.freeze:
            r = self.widget.viewRange()
            data, size = self.probe.get()
            n = data[0][size-1]
            if n >= r[0][1]:
                self.widget.setXRange(n, n + r[0][1] - r[0][0], padding=0)
            self.plot.setData(data[0][:size], data[2][:size])

    def closeEvent(self, event):
        self.probe.close()
        event.accept()

    def pause(self, checked):
        self.freeze = not checked

    def save(self):
        dialog = pg.widgets.FileDialog.FileDialog(self)
        dialog.setAcceptMode(pg.QtGui.QFileDialog.AcceptSave)
        dialog.setFileMode(pg.QtGui.QFileDialog.AnyFile)
        dialog.setDefaultSuffix('csv')
        dialog.setNameFilter('*.csv')
        # dialog.setWindowTitle('Export data to CSV')
        dialog.fileSelected.connect(self.export)
        dialog.show()

    def export(self, fileName):
        exporter = pg.exporters.CSVExporter(self.widget.getPlotItem())
        exporter.export(fileName)

    def zoomOutX(self):
        r = self.widget.viewRange()
        delta = (r[0][1] - r[0][0]) / 16
        self.widget.setXRange(r[0][0] + delta, r[0][1] - delta, padding=0)

    def zoomInX(self):
        r = self.widget.viewRange()
        delta = (r[0][1] - r[0][0]) / 16
        self.widget.setXRange(r[0][0] - delta, r[0][1] + delta, padding=0)

    def zoomOutY(self):
        r = self.widget.viewRange()
        delta = (r[1][1] - r[1][0]) / 8
        self.widget.setYRange(r[1][0], r[1][1] - delta, padding=0)

    def zoomInY(self):
        r = self.widget.viewRange()
        delta = (r[1][1] - r[1][0]) / 8
        self.widget.setYRange(r[1][0], r[1][1] + delta, padding=0)

    def moveLeft(self):
        r = self.widget.viewRange()
        delta = (r[0][1] - r[0][0]) / 16
        self.widget.setXRange(r[0][0] + delta, r[0][1] + delta, padding=0)

    def moveRight(self):
        r = self.widget.viewRange()
        delta = (r[0][1] - r[0][0]) / 16
        self.widget.setXRange(r[0][0] - delta, r[0][1] - delta, padding=0)

    def moveUp(self):
        r = self.widget.viewRange()
        delta = (r[1][1] - r[1][0]) / 16
        self.widget.setYRange(r[1][0] - delta, r[1][1] - delta, padding=0)

    def moveDown(self):
        r = self.widget.viewRange()
        delta = (r[1][1] - r[1][0]) / 16
        self.widget.setYRange(r[1][0] + delta, r[1][1] + delta, padding=0)

    def showInfo(self):
        pg.QtGui.QDesktopServices.openUrl(pg.QtCore.QUrl('https://github.com'))

    def pin(self, checked):
        if checked:
            self.setWindowFlags(self.windowFlags() |
                                pg.QtCore.Qt.WindowStaysOnTopHint)
        else:
            self.setWindowFlags(self.windowFlags() & ~
                                pg.QtCore.Qt.WindowStaysOnTopHint)

        self.show()

    def handle_error(self, error):
        message = 'No device found' if error == 1 else 'Read failed'
        flags = pg.QtGui.QMessageBox.Abort | pg.QtGui.QMessageBox.Retry
        result = pg.QtGui.QMessageBox.critical(self, 'ERROR', message, flags)
        if result == pg.QtGui.QMessageBox.Retry:
            self.probe.start()
        else:
            self.close()


if __name__ == '__main__':
    app = pg.QtGui.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
