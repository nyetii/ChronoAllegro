#include "image.h"

#include "color.h"
#include "core_configuration.h"
#include "allegro5/bitmap_draw.h"

#include "allegro5/bitmap_io.h"
#include "movement.h"
#include "../entities/entity.h"

ALLEGRO_BITMAP* create_image(char* name)
{
	ALLEGRO_BITMAP* image = al_load_bitmap(name);

	return init(image, name) == 0 ? image : NULL;
}

void draw_resized_image(ALLEGRO_BITMAP* image, int x, int y, int w, int h)
{
	al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, w, h, 0);
}

void draw_rotated_image(ALLEGRO_BITMAP* image, Entity* entity, float angle)
{
	for (int i = 0; i < TAXONOMY->size; ++i)
	{
		TAXONOMY->species[i];
		continue;
	}

	al_draw_tinted_scaled_rotated_bitmap(image, entity->species.color,
		entity->point.x + entity->size.width, entity->point.y + entity->size.height / 2.0f,
		entity->point.x + entity->size.width / 2.0f, entity->point.y + entity->size.height / 2.0f,
		0.1, 0.1, to_radians(angle), 0);
}

void destroy_image(ALLEGRO_BITMAP* image)
{
	al_destroy_bitmap(image);
	free(image);
}