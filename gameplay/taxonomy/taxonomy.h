#pragma once
#include "species.h"

typedef struct Taxonomy
{
	Species* species;
	unsigned int size;
} Taxonomy;

Taxonomy* create_taxonomy();

int destroy_taxonomy(Taxonomy* taxonomy);

// Species
int add_species(Taxonomy* taxonomy, Species* species);

int remove_species(Taxonomy* taxonomy, Species* species);