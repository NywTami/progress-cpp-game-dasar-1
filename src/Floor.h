#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "entities/Monster.h"

class Floor {
private:
    int floor_number;
    bool is_boss_floor;
    Monster* boss_or_monster;

public:
    Floor(int floor_num, bool is_boss, Monster* enemy)
        : floor_number(floor_num), is_boss_floor(is_boss), boss_or_monster(enemy) {}

    ~Floor() {
        if (boss_or_monster) delete boss_or_monster;
    }

    int getFloorNumber() const { return floor_number; }
    bool isBossFloor() const { return is_boss_floor; }
    Monster* getEnemy() const { return boss_or_monster; }
};

#endif
