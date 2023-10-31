#pragma once
#include "../entities/entity.h"

int combat_attack(Entity*, Entity*);

int combat_defend(Entity*, Entity*);

void combat_check_stats(Entity*);

void combat_die(Entity*);