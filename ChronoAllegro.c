// ChronoAllegro.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// ReSharper disable CppIntegralToPointerConversion
// ReSharper disable CppClangTidyPerformanceNoIntToPtr
// ReSharper disable CppClangTidyClangDiagnosticIntConversion
#include <stdio.h>
#include <stdbool.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "core/core_configuration.h"
#include "core/image.h"
#include "core/event_loop.h"
#include "gameplay/taxonomy/taxonomy.h"


int main(void)
{
	// Start-up and configuration

	al_init();

	al_install_keyboard();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

	ALLEGRO_DISPLAY* disp = al_create_display(1280, 720);

	//ALLEGRO_FONT* font = al_create_builtin_font();

	al_init_primitives_addon();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	// Load image

	init(al_init_image_addon(), "image addon");
	
	// ALLEGRO_BITMAP* yanderedev = create_image("yanderedev-image.png");
	
	Taxonomy* taxonomy = create_taxonomy();
	/*Species* species = malloc(sizeof * species);
	species->name = "paulo";

	add_species(species);*/

	create_species("paulo", "entities/lion.png", 1000, 500, 500);

	int s = create_species("pedro", "entities/arrow3.png", 1000, 500, 500);

	create_species("matheus", "entities/arrow3.png", 1000, 500, 500);
	/*Species* species2 = malloc(sizeof * species2);
	species2->name = "pedro";
	add_species(species2);*/

	/*Species* species3 = malloc(sizeof * species3);
	species3->name = "matheus";
	add_species(species3);*/


	for (int i = 0; i < taxonomy->size; ++i)
	{
		printf("\n\n%s\n", taxonomy->species[i].name);
	}

	//remove_species(taxonomy->species[s]);
	for (int i = 0; i < taxonomy->size; ++i)
	{
		printf("\n\n%s\n", taxonomy->species[i].name);
	}

	// This is where the event loop starts

	run_event_loop(queue, timer, taxonomy);

	// Shutdown
	//destroy_image(yanderedev);

	
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
