#include "../entities/entity.h"
#include "combat.h"

#include <stdio.h>

int combat_attack(Entity* offender, Entity* defendant)
{
	int ratio = 0;

	if (offender->cooldown <= 0) 
	{
		int defense = combat_defend(defendant, offender);

		ratio = offender->species.atk - defense;
		printf("\nDamage: %d", ratio);

		defendant->species.hp -= ratio;

		offender->cooldown = 40;
	}


	combat_check_stats(offender);
	combat_check_stats(defendant);

	return ratio;
}

int combat_defend(Entity* defendant, Entity* offender)
{
	return rand() % defendant->species.def;
}

void combat_check_stats(Entity* entity)
{
	if (entity->species.hp <= 0)
		combat_die(entity);
}

void combat_die(Entity* entity)
{
	entity->alive = false;
	printf("\n%s is dead", entity->species.name);
}