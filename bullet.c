#include "startrek.h"

int Init_bullet(Bullet *s,int sx,int sy){//初始化子弹
    s->x = sx;
    s->y = sy;
    s->speed = 50;
    s->gone = 0;
    return 0;
}

int Draw_bullet(Bullet *s){//画出子弹
    if(s->gone == 0){
//        al_draw_filled_rectangle(s->x-3,s->y,s->x+3,s->y-10,al_map_rgb(225,225,225));
        al_draw_bitmap(bullet_image,s->x - 8,s -> y - 30,0);
    }
    return 0;
}

int Move_bullet(Bullet *s){//移动子弹
    if(s->gone == 0){

        s->y -= s->speed;
    }

    if(s->y < 0){

        s->gone = -1;

    }
    return 0;
}

int Gone_bullet(Bullet *b){//将子弹设置成已报废
    b->gone = -1;
    return 0;
}
