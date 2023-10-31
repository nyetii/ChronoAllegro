#pragma once
#include "entity.h"

#include <stdlib.h>

#include "../core/image.h"
#include "../gameplay/taxonomy/taxonomy.h"

Entity* create_player(const Taxonomy* taxonomy)
{
	Entity*	player = malloc(sizeof *player);

	ALLEGRO_BITMAP* bmp = TAXONOMY->species[0].sprite;

	player->species = TAXONOMY->species[0];
	player->species.sprite = TAXONOMY->species[0].sprite;
	player->type = PLAYER;
	player->point.x = 100;
	player->point.y = 100;
	player->size.width = al_get_bitmap_width(bmp) * 0.1;
	player->size.height = al_get_bitmap_height(bmp) * 0.1;
	player->angle = 181;

	return player;
}

Entity* create_npc(const Taxonomy* taxonomy, const int index)
{
	Entity* npc = malloc(sizeof * npc);

	npc->species = TAXONOMY->species[index];
	npc->species.sprite = TAXONOMY->species[index].sprite;
	npc->type = NPC;
	npc->point.x = 100;
	npc->point.y = 100;
	npc->size.width = al_get_bitmap_width(npc->species.sprite) * 0.1;
	npc->size.height = al_get_bitmap_height(npc->species.sprite) * 0.1;
	npc->angle = 0;

	return npc;
}