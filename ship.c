#include "startrek.h"

int Init_ship(Ship *s){//初始化飞船
    s->sx = 600;
    s->sy = 240;
    return 0;
}

int Draw_ship(Ship *s,int x,int y){//画出飞船
    s->sx=x;
    s->sy=y;

    al_draw_bitmap(ship_image,s->sx - 37,s->sy - 4,0);
    return 0;
}


