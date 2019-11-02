#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h> 

    void turn_led_on(ALLEGRO_BITMAP * led_on, int location);

    void turn_led_off(ALLEGRO_BITMAP * led_off, int location);

    void initialize_leds(ALLEGRO_BITMAP * background, ALLEGRO_BITMAP * led_off);
    
    static int location[8] = {15,75,135,195,255,315,375,435};
    
    void make_sound (ALLEGRO_SAMPLE *sample);

int main(int argc, char** argv) {

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *led_off = NULL;
    ALLEGRO_BITMAP *led_on = NULL;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_SAMPLE *sample = NULL;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    
    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
    
    if (!al_init_image_addon()) { 
        fprintf(stderr, "failed to initialize image addon!\n");
        return -1;
    }

    led_off = al_load_bitmap("led_off.png");
    if (!led_off) {
        fprintf(stderr, "failed to load image !\n");
        return -1;
    }
    
    led_on = al_load_bitmap("led_on.png");
    if (!led_on) {
        fprintf(stderr, "failed to load image !\n");
        return -1;
    }
    
    background = al_load_bitmap("copper.jpg");
    if (!background) {
        fprintf(stderr, "failed to load background!\n");
        return -1;
    }

    display = al_create_display(500, 100);
    if (!display) {
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(led_on);
        al_destroy_bitmap(background);
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    
    if (!al_install_audio()) {
        fprintf(stderr, "failed to initialize audio!\n");
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(led_on);
        al_destroy_bitmap(background);
        al_destroy_display(display);
        return -1;
    }

    if (!al_init_acodec_addon()) {
        fprintf(stderr, "failed to initialize audio codecs!\n");
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(led_on);
        al_destroy_bitmap(background);
        al_destroy_display(display);
        al_uninstall_audio();
        return -1;
    }

    if (!al_reserve_samples(1)) {
        fprintf(stderr, "failed to reserve samples!\n");
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(led_on);
        al_destroy_bitmap(background);
        al_destroy_display(display);
        return -1;
    }

    sample = al_load_sample("audio.wav");

    if (!sample) {
        printf("Audio clip sample not loaded!\n");
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(led_on);
        al_destroy_bitmap(background);
        al_destroy_sample(sample);
        al_uninstall_audio();
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return -1;
    }
    
    al_draw_bitmap(background,0 , 0, 0); 
    
    initialize_leds(background, led_off);
   
    event_queue = al_create_event_queue();
    if(!event_queue) {
      fprintf(stderr, "failed to create an event queue!\n");
      al_destroy_display(display);
      al_destroy_bitmap(background);
      return -1;
   }

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    bool done = false;
    bool is_on[8] = {};
    
    while(!done){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        if(events.type= ALLEGRO_EVENT_KEY_DOWN){
            switch(events.keyboard.keycode){
                case ALLEGRO_KEY_B:
                    al_clear_to_color(al_map_rgb(50,0,49));
                    al_flip_display();
                    break;
                case ALLEGRO_KEY_1:
                    if (is_on[0] == true) {
                        turn_led_off(led_off,location[0]);
                        al_flip_display();
                        turn_led_off(led_off,location[0]);
                        is_on[0]=false;
                    }
                    else {
                        turn_led_on(led_on,location[0]);
                        al_flip_display();
                        turn_led_on(led_on,location[0]);
                        is_on[0]=true;
                    }
                    make_sound(sample);
                    break;
                case ALLEGRO_KEY_2:
                    al_clear_to_color(al_map_rgb(250,250,250));
                    al_flip_display();
                    break;
                case ALLEGRO_KEY_3:
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_flip_display();
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                default:
                    fprintf(stderr, "coso\n");
            }
        }  
        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            done = true;
        }  
    }
    

    al_destroy_display(display);
    al_destroy_bitmap(led_off);
    al_shutdown_image_addon(); 
    al_destroy_event_queue(event_queue);

    return 0;
}


    void turn_led_on(ALLEGRO_BITMAP * led_on, int location) {
        al_draw_bitmap(led_on, location, 25, 0);
    }

    void turn_led_off(ALLEGRO_BITMAP * led_off, int location) {
        al_draw_bitmap(led_off, location, 25, 0);
    }

    void initialize_leds(ALLEGRO_BITMAP * background, ALLEGRO_BITMAP * led_off){
    
    
    al_draw_bitmap(background,0 , 0, 0); 
    int i;
    for (i=0;i<8;i++){
	static int x = 15;
        turn_led_off(led_off, x);
	x+=60;
	}
    al_flip_display();
    al_draw_bitmap(background,0 , 0, 0); 
    for (i=0;i<8;i++){
	static int x = 15;
        turn_led_off(led_off, x);
	x+=60;
	}
    }
    
    void make_sound (ALLEGRO_SAMPLE *sample){
      al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }