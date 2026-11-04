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
        // Existing heroes
        {"Support_Template", 100, 100, 20, 10, "mana", 50, 50},
        {"Knight_Template", 150, 150, 25, 15, "faith", 60, 60},
        {"Archer_Template", 80, 80, 18, 10, "arrows", 10, 10},
        
        // New heroes
        {"Summoner", 90, 90, 15, 12, "mana", 70, 70},           // Support role, summon allies
        {"Hunter", 120, 120, 28, 14, "energy", 40, 40},         // Physical DPS, animal companions
        {"Berserker", 160, 160, 35, 8, "rage", 50, 50},         // Offensive tank, high damage
        {"Paladin", 140, 140, 22, 20, "holy_power", 45, 45},    // Tank/Support hybrid
        {"Marksman", 95, 95, 32, 9, "focus", 60, 60},           // Ranged DPS, high crit
        {"Druid", 110, 110, 18, 13, "nature_mana", 55, 55},     // Healer/DPS hybrid, heal over time
        {"Black Mage", 85, 85, 30, 11, "dark_mana", 65, 65},    // Pure magical DPS, debuffs
    };
    
    static constexpr int HERO_COUNT = 10;
    
    static Entity* createHero(int hero_index, const std::string& custom_name);
    static void listAvailableHeroes();
};

#endif
