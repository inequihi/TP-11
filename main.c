#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h>

int main(int argc, char** argv) {

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *led_off = NULL;
    ALLEGRO_BITMAP *led_on = NULL;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

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
        al_destroy_bitmap(background);
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    
    
    al_draw_bitmap(background,0 , 0, 0); 
    
    int i;
    for (i=0;i<8;i++){
	static int x = 15;
	al_draw_bitmap(led_off, x, 25, 0);
	x+=60;
	}
    
    al_flip_display();
   
    event_queue = al_create_event_queue();
    if(!event_queue) {
      fprintf(stderr, "failed to create an event queue!\n");
      al_destroy_display(display);
      al_destroy_bitmap(background);
      return -1;
   }

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    bool done = false;
    
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
                    al_clear_to_color(al_map_rgb(40,150,0));
                    al_flip_display();
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
