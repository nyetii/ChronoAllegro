#pragma once
#include "Point.h"
#include "../physics/collision.h"

typedef enum collided
{
	up = 1,
	left = 2,
	down = 4,
	right = 8
} collided;

typedef struct player
{
	bool alive;
	Point point;

	size size;

	//Point hitbox[2];
	hitbox hitbox;


	collided collided;
} player;

