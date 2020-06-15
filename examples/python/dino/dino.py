import board
import digitalio
import displayio
import time
import os
import adafruit_imageload


button = digitalio.DigitalInOut(board.USR_BTN)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP


display = board.DISPLAY

group = displayio.Group(max_size=8)

# Load bitmap
ground_bmp, palette = adafruit_imageload.load("/img/ground512x12.bmp",
                                              bitmap=displayio.Bitmap,
                                              palette=displayio.Palette)

palette.make_transparent(1)
palette[0] = 0x808000

ground = displayio.TileGrid(ground_bmp, pixel_shader=palette,
                            width=120,
                            height=1,
                            tile_width=2,
                            tile_height=12,
                            x=0,
                            y=192)

for x in range(120):
    ground[x] = x

group.append(ground)

dinosaur_bmp, palette = adafruit_imageload.load("/img/dinosaur132x47.bmp",
                                                bitmap=displayio.Bitmap,
                                                palette=displayio.Palette)

palette.make_transparent(1)
palette[0] = 0x404040

# 44x47
dinosaur = displayio.TileGrid(dinosaur_bmp, pixel_shader=palette,
                              width=1,
                              height=1,
                              tile_width=44,
                              tile_height=47,
                              default_tile=2)

dinosaur.x = 8
dinosaur.y = 160

group.append(dinosaur)

cactus_bmp, palette = adafruit_imageload.load("/img/cactus15x32.bmp",
                                              bitmap=displayio.Bitmap,
                                              palette=displayio.Palette)
palette.make_transparent(1)
palette[0] = 0x008000

cactus = displayio.TileGrid(cactus_bmp, pixel_shader=palette)
cactus.x = 240
cactus.y = 170
group.append(cactus)

cactus2_bmp, palette = adafruit_imageload.load("/img/cactus24x50.bmp",
                                               bitmap=displayio.Bitmap,
                                               palette=displayio.Palette)
palette.make_transparent(1)
palette[0] = 0x008000
cactus2 = displayio.TileGrid(cactus2_bmp, pixel_shader=palette)
cactus2.flip_x = True
cactus2.y = 154
group.append(cactus2)

digital_bmp, palette = adafruit_imageload.load("/img/digital200x25.bmp",
                                               bitmap=displayio.Bitmap,
                                               palette=displayio.Palette)

palette.make_transparent(1)
palette[0] = 0x222222

score = displayio.TileGrid(digital_bmp, pixel_shader=palette,
                           width=3,
                           height=1,
                           tile_width=20,
                           tile_height=25)

score.x = 176
score.y = 4
group.append(score)


def update_score(points):
    score[2] = points % 10
    score[1] = (points // 10) % 10
    score[0] = (points // 100) % 10


game_over_bmp, palette2 = adafruit_imageload.load("/img/game_over190x10.bmp",
                                                  bitmap=displayio.Bitmap,
                                                  palette=displayio.Palette)

palette2.make_transparent(1)
palette2[0] = 0xFF0000

game_over = displayio.TileGrid(game_over_bmp, pixel_shader=palette2)

game_over.x = 240
game_over.y = 100
game_over.hidden = True
group.append(game_over)

cloud_bmp, palette2 = adafruit_imageload.load("/img/cloud92x27.bmp",
                                              bitmap=displayio.Bitmap,
                                              palette=displayio.Palette)

palette2.make_transparent(15)
cloud = displayio.TileGrid(cloud_bmp, pixel_shader=palette2)
cloud.x = 80
cloud.y = 30

group.append(cloud)
display.show(group)

demo = True

while True:
    t = 0
    v = [-32, -16, -8, -6, -5, -4, -3, -2, -2, -1, -1, -1, -1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 8, 16, 32]
    jump = -1

    points = 0
    update_score(0)

    dinosaur.y = 160
    cactus.x = 240
    cactus2.x = 480

    while True:
        for x in range(120):
            ground[x] = (t + x) & 0xFF

        cactus.x -= 2
        if cactus.x < -15:
            cactus.x = cactus2.x + 240 + 2 * os.urandom(1)[0]
            print((cactus.x, cactus2.x))

        cactus2.x -= 2
        if cactus2.x < -24:
            cactus2.x = cactus.x + 240 + 2 * os.urandom(1)[0]
            print((cactus.x, cactus2.x))

        if t & 7 == 0:
            cloud.x -= 1
            if cloud.x < -92:
                cloud.x = 240 + (os.urandom(1)[0] & 0xF)

        if jump < 0 and button.value == 0:
            jump = 0
            dinosaur[0, 0] = 2
            if demo:
                demo = False
                points = 0
                update_score(0)
                palette[0] = 0xCCCCCC
                dinosaur.pixel_shader = palette

        if demo and jump < 0 and (cactus.x == 52 or cactus2.x == 52):
            jump = 0
            dinosaur[0, 0] = 2

        if jump >= 0:
            dinosaur.y += v[jump]
            jump += 1
            if jump >= len(v):
                jump = -1
        else:
            if t & 7 == 0:
                dinosaur[0, 0] = (t >> 3) & 1

        if cactus.x == 0 or cactus2.x == 0:
            points += 1
            update_score(points)

        display.show(group)

        if (8 < cactus.x and cactus.x < 36 and (dinosaur.y + 44) >= cactus.y) or (8 < cactus2.x and cactus2.x < 36 and (dinosaur.y + 44) >= (cactus2.y)):
            print((cactus.x, cactus2.x, dinosaur.y))
            game_over.hidden = False
            game_over.x = 25
            display.show(group)
            time.sleep(1)
            while button.value:
                time.sleep(0.1)

            time.sleep(1)
            while not button.value:
                time.sleep(0.1)
            game_over.x = 240
            game_over.hidden = True
            print('restart')
            break

        t = (t + 1) & 0xFF
        # time.sleep(0.05)
