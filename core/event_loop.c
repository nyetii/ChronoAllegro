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
#include "../entities/entity.h"

int run_event_loop(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, Taxonomy* taxonomy)
{
	ALLEGRO_FONT* font = al_create_builtin_font();

	ALLEGRO_BITMAP* yanderedev = create_image("entities/yanderedev-image2.png");

	bool redraw = true;
	bool close = false;
	ALLEGRO_EVENT event;

	Entity* enemy[20];
	Entity* player = create_player(taxonomy);
	//Entity* player = malloc(sizeof * player);
	//Player* player =
	//	malloc(sizeof *player);
	
	/*player->point.x = 100;
	player->point.y = 100;
	player->size.width = 64;
	player->size.height = 128;*/

	int count = 0;
	//Entity* enemy = create_npc(taxonomy, 1);

	//enemy->point.x = 200;
	//enemy->point.y = 200;
	//enemy->size.width = 30;
	//enemy->size.height = 30;

	//float x, y;
	//x = 100;
	//y = 100;
	srand(time(NULL));
	for (int i = 0; i < 20; ++i)
	{
		enemy[i] = create_npc(taxonomy, 1);

		create_hitbox(&enemy[i]->hitbox, enemy[i]->point, enemy[i]->size);
	}

	ALLEGRO_KEYBOARD_STATE ks;

	al_start_timer(timer);
	while (true)
 	{
		for(int i = 0; i < 20; ++i)
		{
			if(enemy[i]->alive == false)
				enemy[i] = create_npc(taxonomy, 1);

			create_hitbox(&enemy[i]->hitbox, enemy[i]->point, enemy[i]->size);
		}
		/*if(count == 0)
		{
			
			
			count = 120;
		}
		--count;*/
		//Player->hitbox.center.x = Player->point.x;
		//Player->hitbox.center.y = Player->point.y;
		create_hitbox(&player->hitbox, player->point, player->size);
		

		//Player->hitbox[1].x = Player->point.x + 10;
		//Player->hitbox[1].y = Player->point.y + 10;

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

		// Enemy logic
		/*if(Enemy->point.x < Player->point.x)
			Enemy->point.x += 0.1f;

		if(Enemy->point.x > Player->point.x)
			Enemy->point.x -= 0.1f;

		if(Enemy->point.y < Player->point.y)
			Enemy->point.y += 0.1f;

		if (Enemy->point.y > Player->point.y)
			Enemy->point.y -= 0.1f;*/

		//const Point direction = calculate_direction(enemy->hitbox, player->hitbox);

		// Move the Enemy towards the Player by the specified speed
		//enemy->point.x += direction.x * 0.2f;
		//enemy->point.y += direction.y * 0.2f;

		for (int i = 0; i < 20; ++i)
		{
			if (enemy[i]->alive == true)
				npc_movement(enemy[i], player->hitbox);
		}
		

		if (redraw && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(20, 20, 20));
			//al_draw_text(font, al_map_rgb(255, 20, 255), 50, 60, 0, "Hi there!");
			//al_draw_tinted_bitmap(yanderedev, al_map_rgba(100, 0, 255, 255), 100, 100, 0);

			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", player->point.x, player->point.y);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 20, 0, "HP: %d", player->species.hp);

			//al_draw_filled_rectangle(player->point.x, player->point.y, player->point.x + player->size.width, player->point.y + player->size.height, get_color(0x4080c4));

			//ALLEGRO_BITMAP* p = player->species.sprite;
			
			//al_draw_bitmap(p, 10, 10, 0);
			//draw_resized_image(player->species.sprite, player->point.x, player->point.y, 10, 10);
			draw_rotated_image(player->species.sprite, player, player->angle);
			
			
			//al_draw_filled_rectangle(enemy->point.x, enemy->point.y, enemy->point.x + enemy->size.width, enemy->point.y + enemy->size.height, get_color(0xFF80c430));

			for (int i = 0; i < 20; ++i) 
			{
				if(enemy[i]->alive == true)
					draw_rotated_image(enemy[i]->species.sprite, enemy[i], enemy[i]->angle);

				al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 40 + (i * 10), 0, "NPC %d (X: %.1f Y: %.1f)", i, enemy[i]->point.x, enemy[i]->point.y);
			}

			al_flip_display();



			redraw = false;
		}
	}

	free(player);
	//free(enemy);
	al_destroy_font(font);
	
	return 0;
}
