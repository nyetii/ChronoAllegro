#pragma once
#include <allegro5/keyboard.h>

#include "../entities/Player.h"
void movement(const ALLEGRO_KEYBOARD_STATE ks, Player* player);

float to_radians(float degree);

float to_degrees(float radians);