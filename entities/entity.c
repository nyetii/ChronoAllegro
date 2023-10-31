#pragma once
#include "entity.h"

#include <math.h>
#include <stdlib.h>

#include "../core/image.h"
#include "../gameplay/taxonomy/taxonomy.h"

Entity* create_player(const Taxonomy* taxonomy)
{
	Entity*	player = malloc(sizeof *player);

	ALLEGRO_BITMAP* bmp = TAXONOMY->species[0].sprite;

	player->species = TAXONOMY->species[0];
	player->species.sprite = TAXONOMY->species[0].sprite;
	player->cooldown = 120;
	player->wiggle = 0;
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
	npc->alive = true;
	npc->cooldown = 120;
	npc->type = NPC;
	npc->point = spawnpoint();
	npc->size.width = al_get_bitmap_width(npc->species.sprite) * 0.1;
	npc->size.height = al_get_bitmap_height(npc->species.sprite) * 0.1;
	npc->angle = 0;

	return npc;
}

Point spawnpoint(void)
{
	
	int x = rand() % 1280;
	int y = rand() % 720;

	int sign = rand() % 2;

	Point point;

		point.x = x;
		point.y = y;

	return point;
}

bool despawn_entity(Entity* entity)
{
	free(entity);
	return true;
}

int closest(const Entity* entity[], Entity* player, const int length)
{
	int closest = 99999;
	float cdist = 99999;

	for (int i = 0; i < length; ++i)
	{
		const float dist = distance(entity[i]->point, player->point);

		if (dist > cdist)
			continue;

		cdist = dist;
		closest = i;
	}

	return closest;
}