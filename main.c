#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h>

int main(void) {

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *image = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_init_image_addon()) { 
        fprintf(stderr, "failed to initialize image addon!\n");
        return -1;
    }

    image = al_load_bitmap("led_off.png");
    if (!image) {
        fprintf(stderr, "failed to load image !\n");
        return 0;
    }

    display = al_create_display(200*8, 200);
    if (!display) {
        al_destroy_bitmap(image);
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    
    al_flip_display();
    
    int i;
    for (i=0;i<8;i++){
	static int x = 150;
	al_draw_bitmap(image, x, 150, 0); 
	x+=150;
	}
     
    event_queue = al_create_event_queue();
     
    if (event_queue = NULL) {
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }

     al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    bool done;
    
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
    al_destroy_bitmap(image);
    al_shutdown_image_addon(); 
    al_destroy_event_queue(event_queue);

    return 0;
}
