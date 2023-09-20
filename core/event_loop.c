#include <math.h>
#include <stdio.h>

#include "image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/display.h"
#include "allegro5/events.h"
#include "../entities/player.h"
#include "../core/color.h"
#include "movement.h"
#include "../entities/enemy.h"

//float distance(Point p1, Point p2) {
//	return sqrtf(powf(p2.x - p1.x, 2) + powf(p2.y - p1.y, 2));
//}

Point calculateDirection(Point p1, Point p2) {
	Point direction;
	float dist = distance(p1, p2);

	if (dist > 10) {
		direction.x = (p2.x - p1.x) / dist;
		direction.y = (p2.y - p1.y) / dist;
	}
	else {
		direction.x = 0;
		direction.y = 0;
	}

	return direction;
}

int run_event_loop(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer)
{
	ALLEGRO_FONT* font = al_create_builtin_font();

	ALLEGRO_BITMAP* yanderedev = create_image("yanderedev-image.png");

	bool redraw = true;
	bool close = false;
	ALLEGRO_EVENT event;

	player* player =
		malloc(sizeof *player);
	
	player->point.x = 100;
	player->point.y = 100;
	player->size.width = 64;
	player->size.height = 128;


	enemy* enemy = malloc(sizeof * enemy);

	enemy->point.x = 200;
	enemy->point.y = 200;
	enemy->size.width = 30;
	enemy->size.height = 30;
	//float x, y;
	//x = 100;
	//y = 100;

	ALLEGRO_KEYBOARD_STATE ks;

	al_start_timer(timer);
	while (true)
 	{
		//player->hitbox.center.x = player->point.x;
		//player->hitbox.center.y = player->point.y;
		create_hitbox(&player->hitbox, player->point, player->size);
		create_hitbox(&enemy->hitbox, enemy->point, enemy->size);

		//player->hitbox[1].x = player->point.x + 10;
		//player->hitbox[1].y = player->point.y + 10;

		al_wait_for_event(queue, &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:
				al_get_keyboard_state(&ks);

				movement(ks, player);

				if (al_key_down(&ks, ALLEGRO_KEY_ESCAPE))
					close = true;

				redraw = true;
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				close = true;
				break;

			default:
				break;
		}
		
		if (close)
			break;

		// enemy logic
		/*if(enemy->point.x < player->point.x)
			enemy->point.x += 0.1f;

		if(enemy->point.x > player->point.x)
			enemy->point.x -= 0.1f;

		if(enemy->point.y < player->point.y)
			enemy->point.y += 0.1f;

		if (enemy->point.y > player->point.y)
			enemy->point.y -= 0.1f;*/

		Point direction = calculate_direction(enemy->hitbox, player->hitbox);

		// Move the enemy towards the player by the specified speed
		enemy->point.x += direction.x * 0.1f;
		enemy->point.y += direction.y * 0.1f;
		

		if (redraw && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(20, 20, 20));
			al_draw_text(font, al_map_rgb(255, 20, 255), 50, 60, 0, "Hi there!");
			al_draw_tinted_bitmap(yanderedev, al_map_rgba(100, 0, 255, 255), 100, 100, 0);

			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", player->point.x, player->point.y);

			al_draw_filled_rectangle(player->point.x, player->point.y, player->point.x + player->size.width, player->point.y + player->size.height, get_color(0x4080c4));


			al_draw_filled_rectangle(enemy->point.x, enemy->point.y, enemy->point.x + enemy->size.width, enemy->point.y + enemy->size.height, get_color(0xFF80c430));
			
			al_flip_display();



			redraw = false;
		}
	}

	free(player);
	free(enemy);
	al_destroy_font(font);
	
	return 0;
}
