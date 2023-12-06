#pragma once
#include "allegro5/bitmap.h"

typedef struct Species
{
	char* name;
	ALLEGRO_BITMAP* sprite;
	ALLEGRO_COLOR color;

	int hp;
	int atk;
	int def;
	float speed;

	struct Species* evolution;
	int playable;
	int minimum_level;
} Species;

int create_species(char* name, char* sprite, int hp, int atk, int def, float speed, int level, int playable);

Species* get_species(const char* name);

void set_evolution(char* species, char* evolution);

void populate_species(void);