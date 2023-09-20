#pragma once
#include "allegro5/bitmap.h"

ALLEGRO_BITMAP* create_image(char* name);

void destroy_image(ALLEGRO_BITMAP* image);
