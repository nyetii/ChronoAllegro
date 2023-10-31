#pragma once
#include <allegro5/keyboard.h>

#include "../entities/Player.h"
#include "../entities/entity.h"

typedef enum Movement
{
	UP = 1,
	LEFT = 2,
	DOWN = 4,
	RIGHT = 8
};

void movement(const ALLEGRO_KEYBOARD_STATE ks, Player* player);

void npc_movement(Entity* entity, Entity* player);

float to_radians(float degree);

float to_degrees(float radians);