#pragma once
#include "entity.h"

#include <math.h>
#include <stdlib.h>

#include "../core/image.h"
#include "../gameplay/taxonomy/taxonomy.h"

Entity* create_player()
{
	Entity*	player = malloc(sizeof *player);

	ALLEGRO_BITMAP* bmp = TAXONOMY->species[0].sprite;

	player->species = TAXONOMY->species[0];
	player->species.sprite = TAXONOMY->species[0].sprite;
	player->species.evolution = TAXONOMY->species[0].evolution;
	player->cooldown = 120;
	player->wiggle = 0;
	player->type = PLAYER;
	player->point.x = 100;
	player->point.y = 100;
	player->size.width = al_get_bitmap_width(bmp) * 0.1;
	player->size.height = al_get_bitmap_height(bmp) * 0.1;
	player->angle = 181;
	player->exp = 0;

	return player;
}

void evolve(Entity* player)
{
	Species evolution = *player->species.evolution;
	player->species = evolution;
}

Entity* create_npc(const int index)
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

Entity* create_npc_any(Entity* player)
{
	const int index = first_not_playable(player);

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

int first_not_playable(Entity* player)
{

	int random = rand() % TAXONOMY->size;

	if (TAXONOMY->species[random].playable == 1 || TAXONOMY->species[random].minimum_level > player->exp)
		random = first_not_playable(player);

	return random;
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