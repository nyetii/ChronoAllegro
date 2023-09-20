#include "core_configuration.h"

#include <stdio.h>

int init(const void* object, char* name)
{
	if (!object)
	{
		printf("Could not initialize %s.\n", name);
		return 1;
	}

	printf("Successfully initialized %s.\n", name);
	return 0;
}
