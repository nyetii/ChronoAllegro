#include "movement.h"

#include <math.h>
#include <stdio.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>

#include "../entities/entity.h"
#include "../gameplay/combat.h"

#define PI 3.14159265358979323846

void movement(const ALLEGRO_KEYBOARD_STATE ks, Entity* player)
{
	--player->cooldown;

	double radians = to_radians(player->angle);
	if (radians > 2 * PI)
		player->angle = to_degrees(radians - (2 * PI));

	if (radians < 0)
		player->angle = to_degrees(radians + (2 * PI));

	//printf("\nRadians: %.2f", to_radians(player->angle));
	if (al_key_down(&ks, ALLEGRO_KEY_UP))
	{
		/*if (player->angle >= 1.0f && player->angle < 180.0f)
			player->angle -= 1.0f;
		else if (player->angle <= 359.0f && player->angle >= 180.0f)
			player->angle += 1.0f;
		else
			player->angle = 0.0f;*/

		

		if (player->angle < 180.0 && player->angle > 0.0)
			player->angle -= 1.0f;
		else
			player->angle += 1.0f;

		player->point.y--;
	}

	if (al_key_down(&ks, ALLEGRO_KEY_DOWN))
	{
		/*if (player->angle >= 1.0f && player->angle < 179.0f)
			player->angle += 1.0f;
		else if (player->angle <= 360.0f && player->angle > 180.0f)
			player->angle -= 1.0f;
		else
			player->angle = 180.0f;*/

		if (player->angle < 180.0 && player->angle > 0.0)
			player->angle += 1.0f;
		else
			player->angle -= 1.0f;

		player->point.y++;
	}

	if (al_key_down(&ks, ALLEGRO_KEY_LEFT))
	{
		/*if (player->angle <= 269.0f && player->angle > 90.0f)
			player->angle += 1.0f;
		else if (player->angle <= 90.0f && player->angle > 269.0f)
			player->angle -= 1.0f;
		else
			player->angle = 270.0f;*/

		if (player->angle > 270 || player->angle < 90)
			player->angle -= 1.0f;
		else
			player->angle += 1.0f;

		player->point.x--;
	}

	if (al_key_down(&ks, ALLEGRO_KEY_RIGHT))
	{
		/*if (player->angle > 91.0f && player->angle <= 270.0f)
			player->angle -= 1.0f;
		else if (player->angle >= 270.0f && player->angle > 450.0f || player->angle >= -90 && player->angle <= 90)
			player->angle += 1.0f;
		else
			player->angle = 90.0f;*/

		if (player->angle > 270 || player->angle < 90)
			player->angle += 1.0f;
		else
			player->angle -= 1.0f;
		

		player->point.x++;
	}

	int rng = rand() % 2;

	if (player->wiggle == 0)
		player->wiggle += rng == 0 ? -1 : 1;
	if (player->wiggle == 1)
		--player->wiggle;
	if (player->wiggle == -1)
		++player->wiggle;

	player->angle += player->wiggle * 3;

	// Attack
	if (al_key_down(&ks, ALLEGRO_KEY_E))
	{
		player->key_pressed = ALLEGRO_KEY_E;
	}
}

void npc_movement(Entity* entity, Entity* player)
{
	--entity->cooldown;
	const Point direction = calculate_direction(entity->hitbox, player->hitbox);

	if(direction.x == 0 && direction.y == 0)
	{
		combat_attack(entity, player);
	}

	double deltaY = player->hitbox.top_left.y - entity->point.y;
	double deltaX = player->hitbox.top_left.x - entity->point.x;

	double tan = atan2(deltaY, deltaX);

	//double angle = p_hitbox.center.y + 10.0 / entity->point.x;
	entity->angle = to_degrees(tan);

	// Move the Enemy towards the Player by the specified speed
	entity->point.x += direction.x * 0.2f;
	entity->point.y += direction.y * 0.2f;
}

float to_radians(float degree)
{
	return degree * (PI / 180.0);
}

float to_degrees(float radians)
{
	return radians * (180.0 / PI);
}