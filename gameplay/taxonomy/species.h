#pragma once
#include "allegro5/bitmap.h"

typedef struct Species
{
	char* name;
	ALLEGRO_BITMAP* sprite;

	int hp;
	int atk;
	int def;
} Species;

int create_species(char* name, char* sprite, int hp, int atk, int def);