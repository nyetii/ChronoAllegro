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

	//int r = playable == 1 ? 255 : rand() % 256;
	//int g = playable == 1 ? 255 : rand() % 256;
	//int b = playable == 1 ? 255 : rand() % 256;
	
	species.color = al_map_rgb(255, 255, 255);
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
	create_species("Mion", "assets/lion.png", 1000, 500, 500, 0.2f, 0, 1);

	create_species("Mion Vermelho", "assets/lion1.png", 1200, 550, 530, 0.3f, 3, 1);

	create_species("Mion Chifrudo", "assets/lion2.png", 1400, 650, 620, 0.4f, 6, 1);

	create_species("Grande Mion", "assets/lion2.png", 1500, 750, 720, 0.5f, 10, 1);

	create_species("Mion Legado", "assets/lion3.png", 1700, 850, 800, 0.6f, 15, 1);


	set_evolution("Mion", "Mion Vermelho");

	set_evolution("Mion Vermelho", "Mion Chifrudo");

	set_evolution("Mion Chifrudo", "Grande Mion");

	set_evolution("Grande Mion", "Mion Legado");
	

	create_species("Myon Classico", "assets/generic.png", 920, 500, 700, 0.2f, NULL, -1);

	create_species("Dragora", "assets/dragora.png", 1100, 800, 250, 0.4f, 3, -1);

	create_species("Chabato", "assets/chabato.png", 1400, 240, 500, 0.6f, 5, -1);

	create_species("Flashes", "assets/flashes.png", 700, 700, 300, 0.8f, NULL, -1);

	create_species("Quaberto", "assets/quaberto.png", 2000, 800, 1000, 0.2f, 8, -1);
}