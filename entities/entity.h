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
	Point point;

	Size size;

	Species species;

	//Point hitbox[2];
	hitbox hitbox;
} Entity;

Entity* create_player(Taxonomy* taxonomy);

Entity* create_npc(Taxonomy* taxonomy);

bool is_out_of_screen(Entity* entity);

bool despawn_entity(Entity* entity);