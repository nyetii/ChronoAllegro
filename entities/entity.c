#pragma once
#include "entity.h"

#include <stdlib.h>

#include "../core/image.h"

Entity* create_player(const Taxonomy* taxonomy)
{
	Entity*	player = malloc(sizeof *player);

	player->species = taxonomy->species[0];
	player->species.sprite = create_image("entities/yanderedev-image2.png");
	player->type = PLAYER;
	player->point.x = 100;
	player->point.y = 100;
	player->size.width = 64;
	player->size.height = 128;

	return player;
}
