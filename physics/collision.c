#include "collision.h"

#include <corecrt_math.h>
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
	
	printf("distance %.2f and radius %.2f\n", dist, distance(p2.top_left, p2.center));

	//printf("Top-Left     - X:%.2f Y:%.2f\n", p2.top_left.x,     p2.top_left.y);
	//printf("Top-Right    - X:%.2f Y:%.2f\n", p2.top_right.x,    p2.top_right.y);
	//printf("Center       - X:%.2f Y:%.2f\n", p2.center.x,       p2.center.y);
	//printf("Bottom-Left  - X:%.2f Y:%.2f\n", p2.bottom_left.x,  p2.bottom_left.y);
	//printf("Bottom-Right - X:%.2f Y:%.2f\n", p2.bottom_right.x, p2.bottom_right.y);

	printf("Player Top-Left X is bigger than enemy Top-Right? \n Player - X:%.2f Y:%.2f\n Enemy - X:%.2f Y:%.2f\n\n",
		p2.top_left.x, p2.top_left.y, p1.top_right.x, p1.top_right.y);
	printf("Player Top-Left Y is bigger than enemy Bottom-Left? \n Player - X:%.2f Y:%.2f\n Enemy - X:%.2f Y:%.2f\n\n",
		p2.top_left.x, p2.top_left.y, p1.bottom_right.x, p1.bottom_left.y);



	//if (dist > p2.center.x - (p2.top_right.x - (p2.width)) && dist > p2.center.y - (p2.bottom_right.y - (p2.height))) {
	/*if ((p1.center.x - h_radius < p2.top_right.x && (p1.center.y + v_radius > p2.top_right.y && p1.center.y - v_radius < p2.bottom_right.y)) 
		&& (p1.center.x + h_radius > p2.top_left.x && (p1.center.y + v_radius > p2.top_left.y && p1.center.y - v_radius < p2.bottom_left.y))) {*/
	if(p2.top_left.x > p1.top_right.x 
		|| p2.top_right.x < p1.top_left.x
		|| p2.top_left.y > p1.bottom_left.y
		|| p2.bottom_left.y < p1.top_left.y){
		
		printf("actually works\n");
		direction.x = (p2.center.x - p1.center.x) / dist;
		direction.y = (p2.center.y - p1.center.y) / dist;
	}
	else {
		
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