#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>

#include "../entities/entity.h"

void movement(const ALLEGRO_KEYBOARD_STATE ks, Entity* player)
{
	if (al_key_down(&ks, ALLEGRO_KEY_UP))
		player->point.y--;

	if (al_key_down(&ks, ALLEGRO_KEY_DOWN))
		player->point.y++;

	if (al_key_down(&ks, ALLEGRO_KEY_LEFT))
		player->point.x--;

	if (al_key_down(&ks, ALLEGRO_KEY_RIGHT))
		player->point.x++;
}
