#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

class Monster : public Entity {
public:
    Monster(string n, int h, int Mh, int atk, int def)
        : Entity(n, h, Mh, atk, def) {}

    void serang(Entity* target) override;
};

#endif
