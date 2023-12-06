#include "species.h"
#include "../../core/image.h"

int create_species(char* name, char* sprite, int hp, int atk, int def, float speed, int level, int playable)
{
	ALLEGRO_BITMAP* bitmap = create_image(sprite);
	Species species =
	{
		.name = name,

		.hp = hp,
		.atk = atk,
		.def = def,
		.speed = speed,

		.playable = playable,
		.minimum_level = level,
	};

	srand(time(NULL));

	int r = playable == 1 ? 255 : rand() % 256;
	int g = playable == 1 ? 255 : rand() % 256;
	int b = playable == 1 ? 255 : rand() % 256;
	
	species.color = al_map_rgb(r, g, b);
	species.sprite = bitmap;
	return add_species(species);
}

Species* get_species(const char* name)
{
	Species* species = NULL;
	for(int i = 0; i < TAXONOMY->size; ++i)
	{
		if (TAXONOMY->species[i].name != name)
			continue;

		species = &TAXONOMY->species[i];
		break;
	}

	return species;
}

void set_evolution(char* species, char* evolution)
{
	for(int i = 0; i < TAXONOMY->size; ++i)
	{
		TAXONOMY->species[i];
		continue;
	}
	get_species(species)->evolution = get_species(evolution);
}

void populate_species(void)
{
	create_species("paulo", "assets/lion.png", 1000, 500, 500, 0.2f, 0, 1);

	create_species("pedro paulo", "assets/lion.png", 1200, 550, 530, 0.3f, 3, 1);

	create_species("super pedro paulo", "assets/lion.png", 1400, 650, 620, 0.4f, 6, 1);

	create_species("o maior pedro paulo", "assets/lion.png", 1500, 750, 720, 0.5f, 10, 1);

	create_species("super o maior pedro paulo", "assets/lion.png", 1700, 850, 800, 0.6f, 15, 1);


	set_evolution("paulo", "pedro paulo");

	set_evolution("pedro paulo", "super pedro paulo");

	set_evolution("super pedro paulo", "o maior pedro paulo");

	set_evolution("o maior pedro paulo", "super o maior pedro paulo");
	

	create_species("matheus", "assets/generic.png", 1000, 500, 500, 0.2f, NULL, -1);
	create_species("almeida", "assets/generic.png", 1000, 500, 500, 0.4f, NULL, -1);
	create_species("saragoca", "assets/arrow3.png", 1000, 500, 500, 0.6f, NULL, -1);
	create_species("julio", "assets/arrow3.png", 1000, 500, 500, 0.8f, NULL, -1);
}