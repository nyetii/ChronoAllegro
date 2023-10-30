#include "image.h"
#include "core_configuration.h"

#include "allegro5/bitmap_io.h"

ALLEGRO_BITMAP* create_image(char* name)
{
	ALLEGRO_BITMAP* image = al_load_bitmap(name);

	return init(image, name) == 0 ? image : NULL;
}

void destroy_image(ALLEGRO_BITMAP* image)
{
	al_destroy_bitmap(image);
	free(image);
}