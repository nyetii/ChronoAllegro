#pragma once
#include "allegro5/events.h"
#include "gameplay/taxonomy/taxonomy.h"

int setup(ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp);

int run_event_loop(ALLEGRO_EVENT_QUEUE*, ALLEGRO_TIMER*, Taxonomy*);
