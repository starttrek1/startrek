#include "startrek.h"

const float FPS = 60;
const int SCREEN_W = 1300;//屏幕宽度
const int SCREEN_H = 700;//屏幕宽度
const int REC_SIZE = 50;

enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ENTER
};

bool key[6] = { false, false, false, false,false,false };
bool redraw = true;
bool doexit = false;
bool keybord = false;
bool Bm = false;
int first;
int Star_number=3;//dentisy
int game_points=0;

int main()
{
    int Bitmap = -330;//背景纵坐标
    int Hb = Bitmap;//记录背景坐标位置
    int score = 0;//分数
    char Score[5];
    int bullet_number = 0;//子弹数量
    int sx = SCREEN_H / 2 - REC_SIZE / 2;
    int sy = SCREEN_W / 2 - REC_SIZE / 2;
    Init_game();
    Menu();
    Asteroid star[Star_number];//彗星数组
    Asteroid star1[Star_number];//彗星数组
    Ship ship[1];//飞船数组
    Bullet bul[500];//子弹数组

    for(int i = 0; i < Star_number; i++){
        Init_star(&star[i]);
        Init_star(&star1[i]);
    }//初始化彗星

    while(!doexit)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(key[KEY_UP] && sy >= 4) {
                sy -= 4;
            }

            if(key[KEY_DOWN] && sy <= SCREEN_H - 65) {
                sy += 4;
            }

            if(key[KEY_LEFT] && sx >= 4) {
                sx -= 4;
            }

            if(key[KEY_RIGHT] && sx <= SCREEN_W-4 ) {
                sx += 4;
            }

            if(key[KEY_SPACE]){
                keybord = true;
            }

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = true;
                break;

            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = true;
                break;

            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = true;
                break;

            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                break;

            case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE] = true;
                break;

            }
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                break;

            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = false;
                break;

            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = false;
                break;

            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                break;

            case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;

            case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE] = false;
                break;

            }
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(255,255,255));
            al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            al_draw_bitmap(image,0,Hb,0);

            if(Hb == 0){
                Bm = true;
            }else if(Hb == Bitmap){
                Bm = false;
            }//当背景坐标到达一定位置时背景向上移动

            if(Bm){
                Hb--;
            }else{
                Hb++;
            }

            for(int i = 0; i < Star_number; i++){
                Move_star(&star[i]);
                Move_star(&star1[i]);
                Draw_star(&star[i]);
                Draw_star1(&star1[i]);

            }//画彗星，移动彗星

            Draw_ship(&ship[0],sx,sy);

            if(keybord)
            {
                Init_bullet(&bul[bullet_number],sx,sy);
                bullet_number++;
                keybord = false;
            }//按下空格发射子弹，子弹数量+1


            for(int i = 0; i < bullet_number; i++){
                Draw_bullet(&bul[i]);
                Move_bullet(&bul[i]);
            }//画子弹，移动子弹

            sprintf(Score,"%d",score);//显示分数
            al_draw_text(font, al_map_rgb(255,255,255), 50, 0,ALLEGRO_ALIGN_CENTRE, Score);

            al_flip_display();

            int x = bullet_number;
            for(int i = 0; i < x; i++){
                if(bul[i].gone == -1){
                    while(i != x)
                    {
                        bul[i] = bul[i+1];
                        i++;
                    }
                    bullet_number--;
                }

            }//当子弹移动到屏幕外，将子弹数后面的之一次向前移

            for(int i = 0; i < Star_number; i++){
                if(star[i].sy > SCREEN_H){
                    Init_star(&star[i]);
                }//当彗星到达屏幕外，重新初始化彗星

                if(star1[i].sy > SCREEN_H){
                    Init_star(&star1[i]);
                    //当彗星到达屏幕外，重新初始化彗星
                }
            }

            for(int z = 0; z < Star_number; z++){
                for(int i = 0; i < bullet_number; i++){

                    if(bul[i].x + 7 > star[z].sx && bul[i].x + 10 < star[z].sx + 125 && bul[i].y - 30 <= star[z].sy + 70){

                        Gone_bullet(&bul[i]);
                        Gone_star(&star[z]);
                        score++;
                    }

                    if(bul[i].x + 7 > star1[z].sx && bul[i].x + 10 < star1[z].sx + 90 && bul[i].y - 30 <= star1[z].sy + 70){

                        Gone_bullet(&bul[i]);
                        Gone_star(&star1[z]);
                        score++;
                    }//判断子弹是否打中彗星，如果打中，分数+1

                }
                if(score > first){
                FILE *A = fopen("../startrek/list.txt","w");
                if(!A){
                    printf("Open failed!");
                }
                fputs(Score,A);
                fclose(A);
}
                if(((ship[0].sx + 30 < star[z].sx + 125) && (ship[0].sx + 30 > star[z].sx) && (ship[0].sy > star[z].sy) && (ship[0].sy < star[z].sy + 70)) || ((ship[0].sx + 30 < star1[z].sx + 90) && (ship[0].sx + 30 > star1[z].sx) && (ship[0].sy > star1[z].sy) && (ship[0].sy < star1[z].sy + 70))) {
                    al_draw_bitmap(fail_image,350,110,0);//判断飞船时候撞上彗星，如果撞上，游戏结束

                    al_flip_display();

                    al_rest(1.0);
                    doexit = true;

                  }
            }

            if(score >= 1000){

                al_draw_text(font, al_map_rgb(255,255,255), SCREEN_W/2, SCREEN_H/2,ALLEGRO_ALIGN_CENTRE, "WIN!");
                al_flip_display();//如果分数达到1000,游戏胜利

                al_rest(3.0);

                doexit = true;
            }

        }

    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);





    return 0;
}

