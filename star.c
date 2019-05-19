#include "startrek.h"


int speed;
int Init_star(Asteroid *s){//初始化飞船



    s->sx = rand()%1400;
    s->sy = rand()%20;
    s->speed = speed;
    s->gone = 0;
    s->move = rand()%3;
    return 0;
}

int Draw_star(Asteroid *s){//画出彗星

    if(s->gone == -1){
        return 0;
    }else{

        al_draw_bitmap(star_image1,s->sx,s->sy,0);

    }

    return 0;
}

int Draw_star1(Asteroid *s){//画出彗星
    if(s->gone == -1){
        return 0;
    }else{
        al_draw_bitmap(star_image,s->sx,s->sy,0);
    }
    return 0;
}

int Move_star(Asteroid *s){//移动彗星

    if(s->gone == -1){
        Init_star(s);
        return 0;
    }else{

        if(s->move == 0)
            s->sy += s->speed;
        else if(s->move == 1){
            s->sy += s->speed;
            s->sx += 1;
        }
        else if(s->move == 2){
            s->sy += s->speed;
            s->sx -= 1;
        }
    }

    return 0;
}

int Gone_star(Asteroid *s){//飞船报废
    s->gone = -1;
    return 0;
}
