#pragma once
#include "taxonomy.h"

#include <stdio.h>
#include <stdlib.h>

Taxonomy* TAXONOMY;

Taxonomy* create_taxonomy(void)
{
	TAXONOMY = malloc(sizeof *TAXONOMY);
	TAXONOMY->species = malloc(sizeof(Species));
	TAXONOMY->species->evolution = malloc(sizeof(Species));
	TAXONOMY->size = 0;
	return TAXONOMY;
}

int destroy_taxonomy(void)
{
	free(TAXONOMY->species);
	free(TAXONOMY);
	return 1;
}

int add_species(Species species)
{
	if (TAXONOMY->size >= 1) 
	{
		Species* new_species = realloc(TAXONOMY->species, (TAXONOMY->size + 1) * sizeof(Species));
		TAXONOMY->species = new_species;
	}

	const int index = (int)TAXONOMY->size;

	TAXONOMY->species[index] = species;
	++TAXONOMY->size;

	//free(species);
	return index;
}

int remove_species(Species species)
{
	//taxonomy = realloc(taxonomy, sizeof(*taxonomy) - sizeof(*species));

	Species* temp = malloc(TAXONOMY->size * sizeof(*temp));

	for(int i = 0, j = 0; i < TAXONOMY->size; ++i)
	{
		if (TAXONOMY->species[i].name == species.name)
			continue;

		temp[j] = TAXONOMY->species[i];
		++j;
	}

	free(TAXONOMY->species);
	--TAXONOMY->size;

	TAXONOMY->species = malloc(TAXONOMY->size * sizeof(Species));

	TAXONOMY->species = temp;

	return 1;
}