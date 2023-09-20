#pragma once
#include "../entities/Point.h"
#include "../physics/collision.h"
typedef struct enemy
{
	bool alive;
	Point point;

	size size;

	hitbox hitbox;
} enemy;