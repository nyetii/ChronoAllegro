#pragma once
#include "allegro5/events.h"
#include "gameplay/taxonomy/taxonomy.h"

int run_event_loop(ALLEGRO_EVENT_QUEUE*, ALLEGRO_TIMER*, Taxonomy*);
