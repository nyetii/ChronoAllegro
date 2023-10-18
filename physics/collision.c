#include "collision.h"

#include <corecrt_math.h>
#include <stdbool.h>
#include <stdio.h>

#include "../entities/Point.h"

float distance(const Point p1, const Point p2)
{
	return sqrtf(powf(p2.x - p1.x, 2) + powf(p2.y - p1.y, 2));
}

Point calculate_direction(const hitbox p1, const hitbox p2)
{
	Point direction;
	const float dist = distance(p1.center, p2.center);

	if(p2.top_left.x > p1.top_right.x 
		|| p2.top_right.x < p1.top_left.x
		|| p2.top_left.y > p1.bottom_left.y
		|| p2.bottom_left.y < p1.top_left.y)
	{
		direction.x = (p2.center.x - p1.center.x) / dist;
		direction.y = (p2.center.y - p1.center.y) / dist;
	}
	else 
	{
		direction.x = 0;
		direction.y = 0;
	}

	return direction;
}

void create_hitbox(hitbox* hitbox, const Point point, const size size)
{
	const float h_radius = size.width / 2.0f;
	const float v_radius = size.height / 2.0f;

	hitbox->top_left.x = point.x;
	hitbox->top_left.y = point.y;
	

	hitbox->center.x = point.x + h_radius;
	hitbox->center.y = point.y + v_radius;

	hitbox->top_right.x = point.x + size.width;
	hitbox->top_right.y = point.y;

	hitbox->bottom_left.x = point.x;
	hitbox->bottom_left.y = point.y + size.height;

	hitbox->bottom_right.x = point.x + size.width;
	hitbox->bottom_right.y = point.y + size.height;

	hitbox->width = hitbox->top_right.x - hitbox->top_left.x;
	hitbox->height = hitbox->bottom_right.y - hitbox->top_left.y;
}