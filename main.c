#include <stdio.h>
#include <allegro5/allegro.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_image.h> //NO OLVIDAR INCLUIR ALLEGRO_IMAGE EN LINKER

int main(void) {

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *image = NULL;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_init_image_addon()) { // ADDON necesario para manejo(no olvidar el freno de mano) de imagenes 
        fprintf(stderr, "failed to initialize image addon !\n");
        return -1;
    }

    image = al_load_bitmap("led_off.png");
    if (!image) {
        fprintf(stderr, "failed to load image !\n");
        return 0;
    }

    display = al_create_display(300, 300*8);
    if (!display) {
        al_destroy_bitmap(image);
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    //void al_draw_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags) 
    int i;
    for (i=0;i<8;i++){
	static int x = 150;
	al_draw_bitmap(image, x, 150, 0); //flags(normalmente en cero, ver doc. para rotar etc)
	x+=150;
	}

    al_flip_display();
    al_rest(5);

    al_destroy_display(display);
    al_destroy_bitmap(image);
    //al_shutdown_image_addon(); VER DOCUMENTACION ES LLAMADO AUTOMATICAMENTE AL SALIR DEL PROGRAMA

    return 0;
}
