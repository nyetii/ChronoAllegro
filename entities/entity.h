#pragma once
#include "Point.h"
#include "../physics/collision.h"
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

	//Point hitbox[2];
	hitbox hitbox;
} Entity;

Entity* create_player(void);