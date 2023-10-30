#pragma once
#include "../entities/Point.h"
#include "../physics/collision.h"
typedef struct Enemy
{
	bool alive;
	Point point;

	Size size;

	hitbox hitbox;
} Enemy;