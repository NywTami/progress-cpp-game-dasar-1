#ifndef HERO_TURN_H
#define HERO_TURN_H

#include <vector>
#include "entities/Entity.h"

void executeHeroTurn(Entity* hero, Entity* monster, std::vector<Entity*>& active_roster);

#endif
