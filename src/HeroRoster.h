#ifndef HERO_ROSTER_H
#define HERO_ROSTER_H

#include <memory>
#include <vector>
#include "entities/Support.h"
#include "entities/Knight.h"
#include "entities/Archer.h"

class HeroRoster {
public:
    // Character stat specifications (easy to tweak)
    static constexpr struct {
        const char* name;
        int hp;
        int max_hp;
        int attack;
        int defense;
        const char* primary_resource;    // mana, faith, arrows, etc.
        int resource_amount;
        int max_resource;
    } HERO_SPECS[] = {
        {"Support", 100, 100, 20, 15, "mana", 50, 50},
        {"Knight", 120, 120, 18, 25, "faith", 60, 60},
        {"Archer", 90, 90, 25, 12, "arrows", 10, 60},
        {"Mage", 80, 80, 30, 10, "mana", 50, 50},
        {"Hunter", 95, 95, 22, 14, "energy", 40, 40},
        {"Berserker", 130, 130, 35, 0, "rage", 0, 300},
    };
    
    static constexpr int HERO_COUNT = 6;
    
    static Entity* createHero(int hero_index, const std::string& custom_name);
    static void listAvailableHeroes();
};

#endif
