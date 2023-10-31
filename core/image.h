#pragma once
#include "allegro5/bitmap.h"
#include "../entities/entity.h"

ALLEGRO_BITMAP* create_image(char* name);

void draw_resized_image(ALLEGRO_BITMAP* image, int x, int y, int w, int h);

void draw_rotated_image(ALLEGRO_BITMAP* image, Entity* entity, float angle);

void destroy_image(ALLEGRO_BITMAP* image);
