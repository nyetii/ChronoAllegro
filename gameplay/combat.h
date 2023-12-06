#pragma once
#include "../entities/entity.h"

int combat_attack(Entity* offender, Entity* defendant);

int combat_defend(Entity*, Entity*);

void combat_check_stats(Entity*);

void combat_die(Entity*);