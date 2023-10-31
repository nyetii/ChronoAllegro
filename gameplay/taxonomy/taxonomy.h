#pragma once
#include "species.h"

typedef struct Taxonomy
{
	Species* species;
	unsigned int size;
} Taxonomy;

Taxonomy* TAXONOMY;

Taxonomy* create_taxonomy(void);

int destroy_taxonomy(void);

// Species
int add_species(Species species);

int remove_species(Species species);