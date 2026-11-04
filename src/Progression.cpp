#include "Progression.h"
#include <iostream>

using namespace std;

Progression::Progression() : current_floor(1) {}

Progression::~Progression() {
    for (auto floor : floors) {
        delete floor;
    }
    floors.clear();
}

void Progression::initializeFloors() {
    for (int i = 1; i <= 10; i++) {
        bool is_boss = (i == 5 || i == 10);
        Monster* enemy = createMonsterForFloor(i);
        floors.push_back(new Floor(i, is_boss, enemy));
    }
    cout << "Progression initialized: 10 floors (Boss at floor 5 and 10)\n";
}

Floor* Progression::getCurrentFloor() const {
    if (current_floor >= 1 && current_floor <= 10) {
        return floors[current_floor - 1];
    }
    return nullptr;
}

bool Progression::nextFloor() {
    if (current_floor < 10) {
        current_floor++;
        return true;
    }
    return false;
}

Monster* Progression::createMonsterForFloor(int floor_num) {
    // Floor 1-4: Regular Goblin/Skeleton enemies
    if (floor_num <= 4) {
        int hp_base = 100 + (floor_num * 50);
        int atk_base = 15 + (floor_num * 3);
        int def_base = 8 + (floor_num * 2);
        
        if (floor_num % 2 == 0) {
            return new Monster("Skeleton_Lv" + to_string(floor_num), hp_base, hp_base, atk_base, def_base);
        } else {
            return new Monster("Goblin_Lv" + to_string(floor_num), hp_base, hp_base, atk_base, def_base);
        }
    }
    
    // Floor 5: First Boss - Orc Chief
    if (floor_num == 5) {
        return new Monster("Orc Chief (BOSS)", 500, 500, 40, 20);
    }
    
    // Floor 6-9: Stronger monsters
    if (floor_num <= 9) {
        int hp_base = 200 + (floor_num * 60);
        int atk_base = 25 + (floor_num * 4);
        int def_base = 15 + (floor_num * 2);
        
        if (floor_num % 2 == 0) {
            return new Monster("Troll_Lv" + to_string(floor_num), hp_base, hp_base, atk_base, def_base);
        } else {
            return new Monster("Dark Knight_Lv" + to_string(floor_num), hp_base, hp_base, atk_base, def_base);
        }
    }
    
    // Floor 10: Final Boss - Demon King
    if (floor_num == 10) {
        return new Monster("Demon King (FINAL BOSS)", 1000, 1000, 60, 35);
    }
    
    return nullptr;
}
