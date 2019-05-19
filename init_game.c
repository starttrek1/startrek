#include "startrek.h"

extern float FPS;
extern int SCREEN_W;//屏幕宽度
extern int SCREEN_H;//屏幕宽度
extern int REC_SIZE;

 enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ENTER
};

extern bool key[6];
extern bool redraw ;
extern bool doexit ;
extern bool keybord ;
extern bool Bm ;
extern int first;
char a[4];

extern int Star_number;//dentisy

int Menu(){//菜单用于开始游戏或者退出游戏

    int sx = 325;
    int sy = 175;
    bool go= false;
    extern int speed;
    bool board;
    FILE *A = fopen("../startrek/list.txt","r");
    if(!A){
        printf("Open failed!");

    }

    fgets(a,4,A);
    while(!go)
    {
        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);

        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

        if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }else  if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(key[KEY_UP] && sy == 525) {
                sy -= 350.0;
            }

            if(key[KEY_DOWN] && sy == 175) {
                sy += 350.0;
            }

            if(key[KEY_LEFT] && sx == 975.0) {
                sx -= 650.0;
            }

            if(key[KEY_RIGHT] && sx == 325) {
                sx += 650.0;
            }

            if(key[KEY_ENTER]){
                board = true;

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

            case ALLEGRO_KEY_ENTER:
                key[KEY_ENTER] = true;
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

            case ALLEGRO_KEY_ENTER:
                key[KEY_ENTER] = false;
                break;
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            if(sx == 325 && sy == 175){
                    al_draw_rectangle(112,125,538,220, al_map_rgb(25,55,155), 10.0);
                    al_draw_bitmap(easy_image2,113,130,0);
                if(board){
                    Star_number = 6;
                    speed = 2;
                    go = true;
                    board = false;
                    doexit = false;
                    break;
                }
            }else{
                al_draw_bitmap(easy_image2,113,130,0);
            }

            if(sx == 975 && sy == 175){
                al_draw_rectangle(760,125,1188,220, al_map_rgb(25,55,155), 10.0);
                  al_draw_bitmap(hard_image2,763,130,0);

                  if(board){
                      Star_number = 10;
                      go = true;
                      speed = 5;
                      board = false;
                      doexit = false;
                      break;
                  }
            }else{
                al_draw_bitmap(hard_image2,763,130,0);
            }

            if(sx == 325 && sy == 525){
                  al_draw_rectangle(112,475,538,570, al_map_rgb(25,55,155), 10.0);
                  al_draw_bitmap(list_image2,113,480,0);
                if(board){






                    al_draw_text(font, al_map_rgb(255,255,255), 600,340,ALLEGRO_ALIGN_CENTRE,a);//显示最高分

                    al_flip_display();
                    al_rest(0.0);
                    board = false;
                    doexit = false;
                }
            }else{
                al_draw_bitmap(list_image2,113,480,0);
            }

            if(sx == 975 && sy == 525){
                al_draw_bitmap(exit_image2,763,480,0);
                al_draw_rectangle(760,475,1188,570, al_map_rgb(25,55,155), 10.0);

                if(board){
                    go = true;
                    doexit = true;
                    board = false;
                }
            }else{
                al_draw_bitmap(exit_image2,763,480,0);

            }

            al_flip_display();
        }
         al_clear_to_color(al_map_rgb(0,0,0));

    }
    first = atoi(a);

    fclose(A);

    return 0;
}

int Init_game(){//初始化

    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if(!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }

    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        return -1;
    }

    //音频文件载入
    sample = al_load_sample( "../startrek/Numb.wav" );

    if (!sample){
        fprintf(stderr, "Audio clip sample not loaded!\n" );
        return -1;
    }

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();

    font = al_load_ttf_font("../startrek/a.ttf",72,0);

    if (!font){
        fprintf(stderr, "Could not load 'a.ttf'.\n");
        return -1;
    }

    if(!al_init_image_addon()) {
        fprintf(stderr,"Failed to initialize al_init_image_addon!");
        return -1;
    }


    image = al_load_bitmap("../startrek/sky.png");
    ship_image = al_load_bitmap("../startrek/ship.png");
    star_image = al_load_bitmap("../startrek/star1.png");
    star_image1 = al_load_bitmap("../startrek/star2.png");
    easy_image2 = al_load_bitmap("../startrek/easy2.png");
    hard_image2 = al_load_bitmap("../startrek/hard2.png");
    list_image2 = al_load_bitmap("../startrek/list.png");
    exit_image2 = al_load_bitmap("../startrek/exit2.png");
    fail_image = al_load_bitmap("../startrek/failed.png");
    bullet_image = al_load_bitmap("../startrek/bullet.png");

    if(!image ) {
        fprintf(stderr,"Failed to load image!");
        al_destroy_display(display);
        return -1;
    }

    if(!bullet_image ) {
        fprintf(stderr,"Failed to load bullet_image!");
        al_destroy_display(display);
        return -1;
    }

    if(!ship_image) {
        fprintf(stderr,"Failed to load ship_image!");
        al_destroy_display(display);
        return -1;
    }

    if(!star_image) {
        fprintf(stderr,"Failed to load star_image!");
        al_destroy_display(display);
        return -1;
    }

    if(!easy_image2) {
        fprintf(stderr,"Failed to load easy_image2!");
        al_destroy_display(display);
        return -1;
    }

    if(!list_image2) {
        fprintf(stderr,"Failed to load list_image2!");
        al_destroy_display(display);
        return -1;
    }

    if(!hard_image2) {
        fprintf(stderr,"Failed to load hard_image2!");
        al_destroy_display(display);
        return -1;
    }

    if(!star_image1) {
        fprintf(stderr,"Failed to load ship_image1!");
        al_destroy_display(display);
        return -1;
    }

    if(!fail_image) {
        fprintf(stderr,"Failed to load ship_image!");
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    al_start_timer(timer);

    return 0;
}
