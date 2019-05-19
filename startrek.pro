TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    star.c \
    ship.c \
    bullet.c \
    init_game.c
INCLUDEPATH += -I/usr/include/allegro5
LIBS += -L/usr/lib -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec

HEADERS += \
    startrek.h
