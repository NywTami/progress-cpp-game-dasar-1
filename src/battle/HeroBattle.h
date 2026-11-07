#ifndef HERO_BATTLE_H
#define HERO_BATTLE_H

#include <vector>
#include "entities/Entity.h"

bool executeSupportBattle(Entity*, Entity*, std::vector<Entity*>&);
bool executeKnightBattle(Entity*, Entity*, std::vector<Entity*>&);
bool executeArcherBattle(Entity*, Entity*, std::vector<Entity*>&);
bool executeMageBattle(Entity*, Entity*, std::vector<Entity*>&);
bool executeHunterBattle(Entity*, Entity*, std::vector<Entity*>&);
bool executeBerserkerBattle(Entity*, Entity*, std::vector<Entity*>&);

#endif
