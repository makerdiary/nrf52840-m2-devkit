# Dino

This is an endless runner game written in Python, inspired by [Chrome’s Hidden Dino Game](chrome://dino).

![](dino.png)

## Requirements
+ [Adafruit CircuitPython ImageLoad](https://github.com/adafruit/Adafruit_CircuitPython_ImageLoad)

## Setup
1.  Download [Adafruit CircuitPython ImageLoad](https://github.com/adafruit/Adafruit_CircuitPython_ImageLoad) and put the `adafruit_imageload` folder into the `lib` directory of the `CIRCUITPY` drive
2.  copy `dino.py` and the `img` folder to the `CIRCUITPY` drive
3.  Change `code.py` to:

    ```
    import dino
    ```

The file tree is like:

``` sh
CIRCUITPY
├── boot_out.txt
├── code.py
├── dino.py
├── img
│   ├── cactus15x32.bmp
│   ├── cactus24x50.bmp
│   ├── cloud92x27.bmp
│   ├── digital200x25.bmp
│   ├── dinosaur132x47.bmp
│   ├── game_over190x10.bmp
│   └── ground512x12.bmp
└── lib
    └── adafruit_imageload
```