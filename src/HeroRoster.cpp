#include "HeroRoster.h"
#include "entities/Monster.h"
#include "entities/Summoner.h"
#include "entities/Hunter.h"
#include "entities/Berserker.h"
#include <iostream>

using namespace std;

Entity* HeroRoster::createHero(int hero_index, const string& custom_name) {
    if (hero_index < 0 || hero_index >= HERO_COUNT) {
        return nullptr;
    }

    const auto& spec = HERO_SPECS[hero_index];
    string hero_name = custom_name.empty() ? spec.name : custom_name;

    // Existing heroes with specific constructors
    if (hero_index == 0) {  // Support
        return new Support(hero_name, spec.hp, spec.max_hp, spec.attack, spec.defense,
                          spec.resource_amount, spec.max_resource);
    }
    if (hero_index == 1) {  // Knight
        return new Knight(hero_name, spec.hp, spec.max_hp, spec.attack, spec.defense,
                         spec.resource_amount, spec.max_resource);
    }
    if (hero_index == 2) {  // Archer
        return new Archer(hero_name, spec.hp, spec.max_hp, spec.attack, spec.defense,
                         10, 10, spec.resource_amount, spec.max_resource);
    }
    if (hero_index == 3) {  // Summoner
        return new Summoner(hero_name, spec.hp, spec.max_hp, spec.attack, spec.defense,
                           spec.resource_amount, spec.max_resource);
    }
    if (hero_index == 4) {  // Hunter
        return new Hunter(hero_name, spec.hp, spec.max_hp, spec.attack, spec.defense,
                         10, 10, spec.resource_amount, spec.max_resource);
    }
    if (hero_index == 5) {  // Berserker
        return new Berserker(hero_name, spec.hp, spec.max_hp, spec.attack);
    }

    // TODO: New heroes (Summoner, Hunter, Berserker, Paladin, Marksman, Druid, Black Mage)
    // Placeholder: return basic Monster for now
    cout << "Hero " << hero_name << " not yet implemented. Using placeholder.\n";
    return new Monster(hero_name, spec.hp, spec.max_hp, spec.attack, spec.defense);
}

void HeroRoster::listAvailableHeroes() {
    cout << "\n=== Available Heroes ===\n";
    for (int i = 0; i < HERO_COUNT; i++) {
        cout << i << ". " << HERO_SPECS[i].name 
             << " (HP: " << HERO_SPECS[i].max_hp 
             << ", ATK: " << HERO_SPECS[i].attack
             << ", DEF: " << HERO_SPECS[i].defense
             << ", Resource: " << HERO_SPECS[i].primary_resource << ")\n";
    }
}
