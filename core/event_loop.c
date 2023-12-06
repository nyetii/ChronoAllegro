#include <math.h>
#include <stdio.h>
#include <allegro5/allegro_image.h>

#include "core_configuration.h"
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
#include "../gameplay/combat.h"

int run_event_loop(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, Taxonomy* taxonomy)
{
	ALLEGRO_FONT* font = al_create_builtin_font();

	ALLEGRO_BITMAP* grass = create_image("assets/grass.png");

	bool redraw = true;
	bool close = false;
	ALLEGRO_EVENT event;

	const int size = 5;

	Entity* enemy[5];

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

	Entity* player = create_player();

	for (int i = 0; i < size; ++i)
	{
		enemy[i] = create_npc_any(player);

		create_hitbox(&enemy[i]->hitbox, enemy[i]->point, enemy[i]->size);
	}

	ALLEGRO_KEYBOARD_STATE ks;

	al_start_timer(timer);

	bool setup = true;

	

	while (true)
	{
		for (int i = 0; i < size; ++i)
		{
			if (enemy[i]->alive == false)
				enemy[i] = create_npc_any(player);


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

		for (int i = 0; i < size; ++i)
		{
			if (enemy[i]->alive == true)
				npc_movement(enemy[i], player);
			else
				despawn_entity(enemy[i]);
		}

		if (player->species.evolution != NULL && player->exp >= player->species.evolution->minimum_level)
		{
			printf("%s is now ", player->species.name);
			evolve(player);
			printf("%s\n", player->species.name);
		}

		if (player->key_pressed == ALLEGRO_KEY_SPACE)
		{
			int c = closest(enemy, player, size);

			float dist = distance(enemy[c]->point, player->point);

			printf("%.2f\n", dist);
			if (player->cooldown > 0 || dist > 100)
				goto leave;

			printf("Space is pressed");


			combat_attack(player, enemy[c]);
			player->key_pressed = 0;
		}
	leave:

		if (redraw && al_is_event_queue_empty(queue))
		{
			if (player->alive == false)
			{
				printf("\n\nDEAD DEAD DEAD");
				al_clear_to_color(al_map_rgb(20, 20, 20));
				al_draw_textf(font, al_map_rgb(255, 255, 255), 605, 357, 0, "Game Over");
				goto end;
			}

			al_clear_to_color(al_map_rgb(20, 20, 20));


			for (int x = 0; x < 1280; x = x + 16)
				for (int y = 0; y < 720; y = y + 16)
				{
					al_draw_bitmap(grass, x, y, 0);
				}


			//al_draw_text(font, al_map_rgb(255, 20, 255), 50, 60, 0, "Hi there!");
			//al_draw_tinted_bitmap(yanderedev, al_map_rgba(100, 0, 255, 255), 100, 100, 0);

			if ((player->species.evolution == NULL || player->species.evolution->name != "Mion Vermelho") && setup)
			{
				free(player);
				destroy_taxonomy();

				return -1;
			}
			setup = false;


			//al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", player->point.x, player->point.y);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Species: %s", player->species.name);

			char* nil = "None";
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 20, 0, "Next Evolution: %s", player->species.evolution == NULL ? nil : player->species.evolution->name);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 60, 0, "%d kills     %d more kills necessary", player->exp, player->species.evolution == NULL ? 0 : player->species.evolution->minimum_level - player->exp);

			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 40, 0, "HP: %d", player->species.hp);


			//al_draw_filled_rectangle(player->point.x, player->point.y, player->point.x + player->size.width, player->point.y + player->size.height, get_color(0x4080c4));

			//ALLEGRO_BITMAP* p = player->species.sprite;

			//al_draw_bitmap(p, 10, 10, 0);
			//draw_resized_image(player->species.sprite, player->point.x, player->point.y, 10, 10);
			draw_rotated_image(player->species.sprite, player, player->angle);


			//al_draw_filled_rectangle(enemy->point.x, enemy->point.y, enemy->point.x + enemy->size.width, enemy->point.y + enemy->size.height, get_color(0xFF80c430));

			for (int i = 0; i < size; ++i)
			{
				if (enemy[i]->alive == false)
					continue;

				draw_rotated_image(enemy[i]->species.sprite, enemy[i], enemy[i]->angle);
				al_draw_textf(font, al_map_rgb(255, 255, 255), enemy[i]->hitbox.center.x, enemy[i]->hitbox.bottom_left.y + 10, 0, "HP: %d", enemy[i]->species.hp);

				//al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 40 + (i * 10), 0, "NPC %d (X: %.1f Y: %.1f)", i, enemy[i]->point.x, enemy[i]->point.y);
			}

		end:

			al_flip_display();



			redraw = false;
		}
	}

	free(player);
	//free(enemy);
	al_destroy_font(font);

	return 0;
}

int setup(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp)
{

	//ALLEGRO_FONT* font = al_create_builtin_font();

	al_init_primitives_addon();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	// Load image

	init(al_init_image_addon(), "image addon");

	// ALLEGRO_BITMAP* yanderedev = create_image("yanderedev-image.png");

	Taxonomy* taxonomy = create_taxonomy();


	populate_species();
	/*Species* species = malloc(sizeof * species);
	species->name = "paulo";

	add_species(species);*/
	/*Species* species2 = malloc(sizeof * species2);
	species2->name = "pedro";
	add_species(species2);*/

	/*Species* species3 = malloc(sizeof * species3);
	species3->name = "matheus";
	add_species(species3);*/


	/*for (int i = 0; i < taxonomy->size; ++i)
	{
		printf("\n\n%s\n", taxonomy->species[i].name);
	}*/

	////remove_species(taxonomy->species[s]);
	//for (int i = 0; i < taxonomy->size; ++i)
	//{
	//	printf("\n\n%s\n", taxonomy->species[i].name);
	//}

	// This is where the event loop starts

	int code = run_event_loop(queue, timer, taxonomy);

	// Shutdown
	//destroy_image(yanderedev);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	if (code == -1)
	{
		al_init();

		al_install_keyboard();

		ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
		ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

		al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
		al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
		al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

		ALLEGRO_DISPLAY* disp = al_create_display(1280, 720);

		setup(timer, queue, disp);
	}

	

	return 0;
}


