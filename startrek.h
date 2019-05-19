#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP  *image ;
ALLEGRO_BITMAP *ship_image;
ALLEGRO_BITMAP *star_image;
ALLEGRO_BITMAP *star_image1;
ALLEGRO_BITMAP *start_image2;
ALLEGRO_BITMAP *exit_image2;
ALLEGRO_BITMAP *fail_image;
ALLEGRO_BITMAP *easy_image2;
ALLEGRO_BITMAP *hard_image2;
ALLEGRO_BITMAP *list_image2;
ALLEGRO_BITMAP *bullet_image;
ALLEGRO_COLOR color;
ALLEGRO_TRANSFORM transform;
ALLEGRO_FONT *font;
ALLEGRO_SAMPLE *sample;

typedef struct {
    int sx;
    int sy;
    int speed;
    int gone;
    int move;
}Asteroid;//彗星结构体

typedef struct {
    int sx ;
    int sy ;
}Ship;//飞船结构体

typedef struct {
    int x;
    int y;
    int speed;
    int gone;
}Bullet;//子弹结构体

int Init_star(Asteroid *s);
int Draw_star(Asteroid *s);
int Draw_star1(Asteroid *s);
int Move_star(Asteroid *s);
int Init_ship(Ship *s);
int Draw_ship(Ship *s, int x, int y);
int Draw_bullet(Bullet *s);
int Move_bullet(Bullet *s);
int Init_bullet(Bullet *s,int sx,int sy);
int Des_star(Asteroid *s,float sx);
int Gone_bullet(Bullet *b);
int Gone_star(Asteroid *s);
int Menu();
int Init_game();
int Draw_setting(int game_points);
