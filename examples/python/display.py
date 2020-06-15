
import board
import digitalio
import displayio
import time


display = board.DISPLAY

bitmap = displayio.Bitmap(40, 40, 2)
for i in range(40):
    bitmap[i, i] = 1

palette = displayio.Palette(2)
palette[0] = 0x000000
palette[1] = 0x00FF00

tile = displayio.TileGrid(bitmap,
                          pixel_shader=palette,
                          width=6,
                          height=6,
                          tile_width=40,
                          tile_height=40)

group = displayio.Group()
group.append(tile)

display.show(group)

while True:
    time.sleep(1)
