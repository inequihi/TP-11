#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h> 


/////////////////////////FUNCIONES//////////////////////////////////

void turn_led(ALLEGRO_BITMAP * led_image, int location, ALLEGRO_SAMPLE *sample, bool is_on[8], int led_number); //Permite encender o apagar un led

void initialize_leds(ALLEGRO_BITMAP * background, ALLEGRO_BITMAP * led_off); //Inicializa los leds como apagados

void turn_all_leds(ALLEGRO_BITMAP * led_image, ALLEGRO_SAMPLE *sample, bool is_on[8]); //Cambia todos los leds a apagado o encendido

void key_b_func(ALLEGRO_BITMAP * led_image, ALLEGRO_SAMPLE *sample, bool was_on[8]); //Se utiliza para el boton B, que realiza una intermitencia.

void make_sound(ALLEGRO_SAMPLE *sample); //Ejecuta el sonido que realizan los leds al cambiar de estado.

const int location[8] = {15, 75, 135, 195, 255, 315, 375, 435}; //Matriz con la posicion de los leds en el display.


////////////////////////MAIN////////////////////////////////

int main(int argc, char** argv) {

    //Inicializa allegro y sus componentes

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

    al_draw_bitmap(background, 0, 0, 0);

    initialize_leds(background, led_off);

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create an event queue!\n");
        al_destroy_display(display);
        al_destroy_bitmap(background);
        return -1;
    }

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));


    bool done = false; //Cuando es verdadero, se sale del while loop y termina el programa
    bool is_on[8] = {}; //Matriz que lleva la cuenta de que leds est�n prendidos en un momento dado
    bool was_on[8] = {}; //Matriz que lleva la cuenta de que leds estaban prendidos cuando se presiono la tecla b

    int index; //Variable de enteros, que sen usa para un for en la tecla T

    while (!done) { //
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (events.keyboard.keycode) {
                case ALLEGRO_KEY_B: //Al presionar la tecla B, los leds que se encuentren 
                    // encendidos van a parpadear hasta que se vuelva a presionarse.
                    for (index = 0; index < 8; index++) {
                        was_on[index] = is_on[index];
                    }

                    while (events.type == ALLEGRO_EVENT_KEY_DOWN && events.keyboard.keycode == ALLEGRO_KEY_B) {
                        al_get_next_event(event_queue, &events);
                    }//Neutralizamos el eco del input de la letra b
                    al_wait_for_event(event_queue, &events);
                    while (events.type != ALLEGRO_EVENT_KEY_DOWN || events.keyboard.keycode != ALLEGRO_KEY_B) {
                        key_b_func(led_off, sample, was_on);
                        al_rest(0.5);
                        key_b_func(led_on, sample, was_on);
                        al_rest(0.5);
                        al_get_next_event(event_queue, &events);
                    }
                    break;
                case ALLEGRO_KEY_C: //Apaga todos los leds.
                    turn_all_leds(led_off, sample, is_on);
                    break;
                case ALLEGRO_KEY_S: //Encinende todos los leds.
                    turn_all_leds(led_on, sample, is_on);
                    break;
                case ALLEGRO_KEY_T: //Cambia el estado de cada led por su contrario.
                    for (index = 0; index < 8; index++) {
                        if (is_on[index] == false) {
                            turn_led(led_on, location[index], sample, is_on, index);
                        } else {
                            turn_led(led_off, location[index], sample, is_on, index);
                        }
                    }
                    break;

                    //Al presionar un numero del 0 al 7 se encendera/apagara dicho led teniendo en cuenta su estado anterior
                case ALLEGRO_KEY_0:
                    if (is_on[0] == true) {
                        turn_led(led_off, location[0], sample, is_on, 0);
                    } else {
                        turn_led(led_on, location[0], sample, is_on, 0);
                    }
                    break;
                case ALLEGRO_KEY_1:
                    if (is_on[1] == true) {
                        turn_led(led_off, location[1], sample, is_on, 1);
                    } else {
                        turn_led(led_on, location[1], sample, is_on, 1);
                    }
                    break;
                case ALLEGRO_KEY_2:
                    if (is_on[2] == true) {
                        turn_led(led_off, location[2], sample, is_on, 2);
                    } else {
                        turn_led(led_on, location[2], sample, is_on, 2);
                    }
                    break;
                case ALLEGRO_KEY_3:
                    if (is_on[3] == true) {
                        turn_led(led_off, location[3], sample, is_on, 3);
                    } else {
                        turn_led(led_on, location[3], sample, is_on, 3);
                    }
                    break;
                case ALLEGRO_KEY_4:
                    if (is_on[4] == true) {
                        turn_led(led_off, location[4], sample, is_on, 4);
                    } else {
                        turn_led(led_on, location[4], sample, is_on, 4);
                    }
                    break;
                case ALLEGRO_KEY_5:
                    if (is_on[5] == true) {
                        turn_led(led_off, location[5], sample, is_on, 5);
                    } else {
                        turn_led(led_on, location[5], sample, is_on, 5);
                    }
                    break;
                case ALLEGRO_KEY_6:
                    if (is_on[6] == true) {
                        turn_led(led_off, location[6], sample, is_on, 6);
                    } else {
                        turn_led(led_on, location[6], sample, is_on, 6);
                    }
                    break;
                case ALLEGRO_KEY_7:
                    if (is_on[7] == true) {
                        turn_led(led_off, location[7], sample, is_on, 7);
                    } else {
                        turn_led(led_on, location[7], sample, is_on, 7);
                    }
                    break;
                case ALLEGRO_KEY_Q: //Cierra el display.
                    done = true;
                    break;
                default:
                    fprintf(stderr, "Error: invalid key\n");
            }
        }
        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //Cierra el display al presionarse la cruz del mismo.
            done = true;
        }
    }

    //Termina el programa y destruye todos los componentes de allegro.
    al_destroy_display(display);
    al_destroy_bitmap(led_off);
    al_shutdown_image_addon();
    al_destroy_event_queue(event_queue);

    return 0;
}

//////////////////////////////FUNCIONES///////////////////////////////

//Enciende o aparga un led en particular.

void turn_led(ALLEGRO_BITMAP * led_image, int location, ALLEGRO_SAMPLE *sample, bool is_on[8], int led_number) {
    al_draw_bitmap(led_image, location, 25, 0);
    al_flip_display();
    make_sound(sample);
    al_draw_bitmap(led_image, location, 25, 0);
    if (is_on[led_number] == true) {
        is_on[led_number] = false;
    } else if (is_on[led_number] == false) {
        is_on[led_number] = true;
    }
}

//Enciende o apaga todos los leds.    

void turn_all_leds(ALLEGRO_BITMAP * led_image, ALLEGRO_SAMPLE *sample, bool is_on[8]) {
    int led_number;
    for (led_number = 0; led_number < 8; led_number++) {
        al_draw_bitmap(led_image, location[led_number], 25, 0);
        if (is_on[led_number] == false) {
            is_on[led_number] = true;
        }
    }
    make_sound(sample);
    al_flip_display();
    for (led_number = 0; led_number < 8; led_number++) {
        al_draw_bitmap(led_image, location[led_number], 25, 0);
        if (is_on[led_number] == false) {
            is_on[led_number] = true;
        }
    }
}

//Si un led estaba encendido al presionarse la letra b, se va a apagar y encender hasta que se presione nuevamente esta letra.

void key_b_func(ALLEGRO_BITMAP * led_image, ALLEGRO_SAMPLE *sample, bool was_on[8]) {
    int led_number;
    for (led_number = 0; led_number < 8; led_number++) {
        if (was_on[led_number] == true) {
            al_draw_bitmap(led_image, location[led_number], 25, 0);
        }
    }
    make_sound(sample);
    al_flip_display();
    for (led_number = 0; led_number < 8; led_number++) {
        if (was_on[led_number] == true) {
            al_draw_bitmap(led_image, location[led_number], 25, 0);
        }
    }
}

//Inicializa los leds como apagado.

void initialize_leds(ALLEGRO_BITMAP * background, ALLEGRO_BITMAP * led_off) {


    al_draw_bitmap(background, 0, 0, 0);
    int i;
    for (i = 0; i < 8; i++) {
        static int x = 15;
        al_draw_bitmap(led_off, x, 25, 0);
        x += 60;
    }
    al_flip_display();
    al_draw_bitmap(background, 0, 0, 0);
    for (i = 0; i < 8; i++) {
        static int x = 15;
        al_draw_bitmap(led_off, x, 25, 0);
        x += 60;
    }
}

//Produce el sonido de apagar/encender un led.    

void make_sound(ALLEGRO_SAMPLE *sample) {
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}