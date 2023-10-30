#pragma once
#include "../entities/Point.h"
typedef struct hitbox
{
	Point top_left;
	Point top_right;
	Point bottom_left;
	Point bottom_right;

	Point center;
	
	float width;
	float height;
} hitbox;

float distance(Point p1, Point p2);

Point calculate_direction(hitbox p1, hitbox p2);

void create_hitbox(hitbox* hitbox, const Point point, const Size size);