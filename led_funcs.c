/***************************************************************************//**
  @file     +led_funcs.c+
  @brief    +Descripcion del archivo+
  @author   +joaco+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

    #include <stdio.h>
    #include <stdlib.h>
    #include <allegro5/allegro_image.h>
    #include "led_funcs.h"



/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

    ALLEGRO_BITMAP * led_on = NULL;
    ALLEGRO_BITMAP * led_off = NULL;
    ALLEGRO_BITMAP * background = NULL;
    
    al_init();
    al_init_image_addon();
    
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



/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

    const int leds[8]={15,75,135,195,255,315,375,435}; //Posicion en x de los leds

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

    void turn_led_on(int location) {
        al_draw_bitmap(led_on, location, 25, 0);
    }

    void turn_led_off(int location) {
        al_draw_bitmap(led_off, location, 25, 0);
    }

    void initialize_leds(void){
    al_draw_bitmap(background,0 , 0, 0); 
    
    int i;
    for (i=0;i<8;i++){
	static int x = 15;
        turn_led_off(x);
	x+=60;
	}
    
    al_flip_display();
    }
