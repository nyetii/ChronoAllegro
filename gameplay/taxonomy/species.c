#include "species.h"
#include "../../core/image.h"

int create_species(char* name, char* sprite, int hp, int atk, int def)
{
	ALLEGRO_BITMAP* bitmap = create_image(sprite);
	Species species =
	{
		.name = name,

		.hp = hp,
		.atk = atk,
		.def = def,
	};

	species.sprite = bitmap;
	return add_species(species);
}
