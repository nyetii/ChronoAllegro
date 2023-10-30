#pragma once
#include "entity.h"

#include <stdlib.h>

Entity* create_player(void)
{
	Entity*	player = malloc(sizeof *player);

	player->type = PLAYER;
	player->point.x = 100;
	player->point.y = 100;
	player->size.width = 64;
	player->size.height = 128;

	return player;
}
