#include "image.h"
#include "core_configuration.h"
#include "allegro5/bitmap_draw.h"

#include "allegro5/bitmap_io.h"

ALLEGRO_BITMAP* create_image(char* name)
{
	ALLEGRO_BITMAP* image = al_load_bitmap(name);

	return init(image, name) == 0 ? image : NULL;
}

void draw_resized_image(ALLEGRO_BITMAP* image, int x, int y, int w, int h)
{
	al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, w, h, 0);
}

void destroy_image(ALLEGRO_BITMAP* image)
{
	al_destroy_bitmap(image);
	free(image);
}