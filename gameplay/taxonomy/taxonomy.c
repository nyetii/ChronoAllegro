#pragma once
#include "taxonomy.h"

#include <stdio.h>
#include <stdlib.h>

Taxonomy* create_taxonomy()
{
	Taxonomy* taxonomy = malloc(sizeof *taxonomy);
	taxonomy->species = malloc(sizeof(Species));
	taxonomy->size = 0;
	return taxonomy;
}

int destroy_taxonomy(Taxonomy* taxonomy)
{
	free(taxonomy->species);
	free(taxonomy);
	return 1;
}

int add_species(Taxonomy* taxonomy, Species* species)
{
	Species* new_species = realloc(taxonomy->species, 2 * sizeof(Species));
	taxonomy->species = new_species;

	taxonomy->species[taxonomy->size].name = species->name;
	++taxonomy->size;

	free(species);
	return 1;
}

int remove_species(Taxonomy* taxonomy, Species* species)
{
	//taxonomy = realloc(taxonomy, sizeof(*taxonomy) - sizeof(*species));

	Species* temp = malloc(taxonomy->size * sizeof(*species));

	for(int i = 0, j = 0; i < taxonomy->size; ++i)
	{
		if (taxonomy->species[i].name == species->name)
			continue;

		temp[j] = taxonomy->species[i];
		++j;
	}
	//free(taxonomy->species);
	--taxonomy->size;

	//taxonomy->species = malloc(taxonomy->size * sizeof(*species));
	taxonomy->species = realloc(temp, sizeof(*temp));
	taxonomy->species = temp;

	return 1;
}