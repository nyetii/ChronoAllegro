#pragma once
#include "Point.h"
#include "../physics/collision.h"
#include "../gameplay/taxonomy/taxonomy.h"
#include "../gameplay/taxonomy/species.h"
#include <stdbool.h>

typedef enum EntityType
{
	NPC,
	PLAYER
} EntityType;

typedef struct Entity
{
	EntityType type;
	bool alive;
	int cooldown;
	int key_pressed;
	int wiggle;
	Point point;

	Size size;

	Species species;
	float angle;

	//Point hitbox[2];
	hitbox hitbox;
} Entity;

Entity* create_player(Taxonomy* taxonomy);

Entity* create_npc(Taxonomy* taxonomy, int index);

Point spawnpoint(void);

bool is_out_of_screen(Entity* entity);

bool despawn_entity(Entity* entity);

int closest(const Entity* entity[], Entity* player, const int length);