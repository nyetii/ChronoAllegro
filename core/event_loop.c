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

		create_hitbox(&player->hitbox, player->point, player->size);

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


			if ((player->species.evolution == NULL || player->species.evolution->name != "Mion Vermelho") && setup)
			{
				free(player);
				destroy_taxonomy();

				return -1;
			}
			setup = false;


			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Species: %s", player->species.name);

			char* nil = "None";
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 20, 0, "Next Evolution: %s", player->species.evolution == NULL ? nil : player->species.evolution->name);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 60, 0, "%d kills     %d more kills necessary", player->exp, player->species.evolution == NULL ? 0 : player->species.evolution->minimum_level - player->exp);

			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 40, 0, "HP: %d", player->species.hp);

			draw_rotated_image(player->species.sprite, player, player->angle);


			for (int i = 0; i < size; ++i)
			{
				if (enemy[i]->alive == false)
					continue;

				draw_rotated_image(enemy[i]->species.sprite, enemy[i], enemy[i]->angle);
				al_draw_textf(font, al_map_rgb(255, 255, 255), enemy[i]->hitbox.center.x, enemy[i]->hitbox.bottom_left.y + 10, 0, "HP: %d", enemy[i]->species.hp);
			}

		end:

			al_flip_display();



			redraw = false;
		}
	}

	free(player);
	al_destroy_font(font);

	return 0;
}

int setup(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp)
{
	al_init_primitives_addon();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	// Load image

	init(al_init_image_addon(), "image addon");


	Taxonomy* taxonomy = create_taxonomy();


	populate_species();
	
	// This is where the event loop starts

	int code = run_event_loop(queue, timer, taxonomy);

	// Shutdown
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


