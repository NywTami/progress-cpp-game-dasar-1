#include "HeroBattle.h"

#include <iostream>
#include <limits>

#include "entities/Support.h"
#include "entities/Knight.h"
#include "entities/Archer.h"
#include "entities/Mage.h"
#include "entities/Hunter.h"
#include "entities/Berserker.h"

using namespace std;

namespace {
int readChoice(int min_value, int max_value) {
    int choice;
    if (!(cin >> choice) || choice < min_value || choice > max_value) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "❌ Input tidak valid, coba lagi.\n";
        return -1;
    }
    return choice;
}

Entity* chooseTarget(vector<Entity*>& roster, const char* prompt) {
    cout << prompt << " (1-" << roster.size() << "): ";
    int choice;
    if (!(cin >> choice) || choice < 1 || choice > static_cast<int>(roster.size())) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "❌ Target tidak valid.\n";
        return nullptr;
    }
    Entity* target = roster[choice - 1];
    if (!target || !target->isAlive()) {
        cout << "❌ Target tidak aktif.\n";
        return nullptr;
    }
    return target;
}

template <typename T>
void showHeader(T* hero, const char* resource, int current, int maximum) {
    cout << "\n⚔️ Giliran " << hero->getNama() << "\n"
         << "HP: " << hero->getHP() << "/" << hero->getMaxHP() << "\n"
         << resource << ": " << current << "/" << maximum << "\n";
}
}

bool executeSupportBattle(Entity* entity, Entity* monster, vector<Entity*>& roster) {
    auto* hero = dynamic_cast<Support*>(entity);
    showHeader(hero, "Mana", hero->getMana(), hero->getMaxMana());
    cout << "\n1. Basic Attack\n2. Heal (10 mana)\n3. Mass Heal (25 mana)\n4. Regen Mana\n5. Buff Defense (15 mana)\n6. Buff Attack Power (20 mana)\nPilihan: ";
    const int action = readChoice(1, 6);
    if (action < 0) return false;
    if (action == 1) { hero->serang(monster); return true; }
    if (action == 2) {
        if (hero->getMana() < 10) { cout << "❌ Mana tidak cukup (butuh 10).\n"; return false; }
        Entity* target = chooseTarget(roster, "Pilih target heal");
        if (!target) return false;
        hero->heal(target); return true;
    }
    if (action == 3) {
        if (hero->getMana() < 25) { cout << "❌ Mana tidak cukup (butuh 25).\n"; return false; }
        hero->massHeal(roster.size() > 0 ? roster[0] : nullptr,
                       roster.size() > 1 ? roster[1] : nullptr,
                       roster.size() > 2 ? roster[2] : nullptr);
        return true;
    }
    if (action == 4) { hero->regenMana(15); return true; }
    if (hero->getMana() < 20) { cout << "❌ Mana tidak cukup (butuh 20).\n"; return false; }
    Entity* target = chooseTarget(roster, "Pilih target buff");
    if (!target) return false;
    if (action == 5) hero->buffDefense(target);
    else hero->buffAttackPower(target);
    return true;
}

bool executeKnightBattle(Entity* entity, Entity* monster, vector<Entity*>& roster) {
    auto* hero = dynamic_cast<Knight*>(entity);
    showHeader(hero, "Faith", hero->getFaith(), hero->getMaxfaith());
    cout << "\n1. Basic Attack\n2. Power Strike\n3. Ultimate Charge\n4. Shield Block (20 faith)\n5. Regen Faith\n6. Bless Defense (15 faith)\nPilihan: ";
    const int action = readChoice(1, 6);
    if (action < 0) return false;
    if (action == 1) hero->serang(monster);
    else if (action == 2) hero->powerStrike(monster);
    else if (action == 3) hero->ultimateCharge(monster);
    else if (action == 4) {
        if (hero->getFaith() < 20) { cout << "❌ Faith tidak cukup (butuh 20).\n"; return false; }
        hero->shieldBlock();
    } else if (action == 5) hero->regenFaith();
    else {
        if (hero->getFaith() < 15) { cout << "❌ Faith tidak cukup (butuh 15).\n"; return false; }
        Entity* target = chooseTarget(roster, "Pilih target bless");
        if (!target) return false;
        hero->blessDefense(target);
    }
    return true;
}

bool executeArcherBattle(Entity* entity, Entity* monster, vector<Entity*>&) {
    auto* hero = dynamic_cast<Archer*>(entity);
    cout << "\n⚔️ Giliran " << hero->getNama() << "\nHP: " << hero->getHP() << "/" << hero->getMaxHP()
         << "\nArrows: " << hero->getArrows() << "/" << hero->getMaxarrows()
         << " | Mana: " << hero->getMana() << "/" << hero->getMaxmana() << "\n";
    cout << "\n1. Basic Attack (panah)\n2. Basic Attack (tanpa panah)\n3. Special Attack (10 mana, 1 panah)\n4. Reload Arrows\n5. Fire Arrow (10 mana)\n6. Lightning Arrow (15 mana)\n7. Poison Arrow (10 mana)\n8. Multi Shot (15 mana, 2 panah)\n9. Rapid Fire (30 mana)\n10. Regen Mana\nPilihan: ";
    const int action = readChoice(1, 10);
    if (action < 0) return false;
    int mana = 0, arrows = 0;
    switch (action) {
        case 1: if (hero->getArrows() < 1) { cout << "❌ Panah habis; pilih Reload Arrows.\n"; return false; } hero->serang(monster); break;
        case 2: hero->basicAttack(monster); break;
        case 3: mana = 10; arrows = 1; break;
        case 4: hero->reloadArrows(); break;
        case 5: mana = 10; break;
        case 6: mana = 15; break;
        case 7: mana = 10; break;
        case 8: mana = 15; arrows = 2; break;
        case 9: mana = 30; break;
        case 10: hero->regenMana(); break;
    }
    if (action == 1 || action == 2 || action == 4 || action == 10) return true;
    if (hero->getMana() < mana) { cout << "❌ Mana tidak cukup (butuh " << mana << ").\n"; return false; }
    if (hero->getArrows() < arrows) { cout << "❌ Panah tidak cukup (butuh " << arrows << ").\n"; return false; }
    switch (action) {
        case 3: hero->specialAttack(monster); break;
        case 5: hero->fireArrow(monster); break;
        case 6: hero->lightningArrow(monster); break;
        case 7: hero->poisonArrow(monster); break;
        case 8: hero->multiShot(monster); break;
        case 9: hero->rapidFire(monster); break;
    }
    return true;
}

bool executeMageBattle(Entity* entity, Entity* monster, vector<Entity*>&) {
    auto* hero = dynamic_cast<Mage*>(entity);
    showHeader(hero, "Mana", hero->getMana(), hero->getMaxmana());
    cout << "\n1. Basic Attack\n2. Fireball (15 mana)\n3. Ultimate Burst (30 mana)\n4. Regen Mana\nPilihan: ";
    const int action = readChoice(1, 4);
    if (action < 0) return false;
    if (action == 1) hero->serang(monster);
    else if (action == 2) {
        if (hero->getMana() < 15) { cout << "❌ Mana tidak cukup (butuh 15).\n"; return false; }
        hero->fireball(monster);
    } else if (action == 3) {
        if (hero->getMana() < 30) { cout << "❌ Mana tidak cukup (butuh 30).\n"; return false; }
        hero->ultimateBurst(monster);
    } else hero->regenMana(20);
    return true;
}

bool executeHunterBattle(Entity* entity, Entity* monster, vector<Entity*>&) {
    auto* hero = dynamic_cast<Hunter*>(entity);
    showHeader(hero, "Energy", hero->getEnergy(), hero->getMaxEnergy());
    cout << "\n1. Basic Attack\n2. Power Shot (20 energy)\n3. Beast Companion (25 energy)\n4. Tracking Shot (15 energy)\n5. Disadvantage Shot (20 energy)\n6. Hunter's Mark (10 energy)\n7. Regen Energy\nPilihan: ";
    const int action = readChoice(1, 7);
    if (action < 0) return false;
    if (action == 1) hero->serang(monster);
    else if (action == 2) {
        if (hero->getEnergy() < 20) { cout << "❌ Energy tidak cukup (butuh 20).\n"; return false; }
        hero->powerShot(monster);
    } else if (action == 3) {
        if (hero->getEnergy() < 25) { cout << "❌ Energy tidak cukup (butuh 25).\n"; return false; }
        hero->beastCompanion(monster);
    } else if (action == 4) {
        if (hero->getEnergy() < 15) { cout << "❌ Energy tidak cukup (butuh 15).\n"; return false; }
        hero->trackingShot(monster);
    } else if (action == 5) {
        if (hero->getEnergy() < 20) { cout << "❌ Energy tidak cukup (butuh 20).\n"; return false; }
        hero->disadvantageShot(monster);
    } else if (action == 6) {
        if (hero->getEnergy() < 10) { cout << "❌ Energy tidak cukup (butuh 10).\n"; return false; }
        hero->huntersMark(monster);
    } else hero->regenEnergy(20);
    return true;
}

bool executeBerserkerBattle(Entity* entity, Entity* monster, vector<Entity*>&) {
    auto* hero = dynamic_cast<Berserker*>(entity);
    cout << "\n⚔️ Giliran " << hero->getNama() << "\nHP: " << hero->getHP() << "/" << hero->getMaxHP()
         << "\nRage: " << hero->getRage() << "/" << hero->getMaxRage() << "\n";
    cout << "\n1. Basic Attack\n2. Rage Strike\n3. Whirlwind\n4. Self Heal (30 rage)\nPilihan: ";
    const int action = readChoice(1, 4);
    if (action < 0) return false;
    if (action == 1) hero->basicAttack(monster);
    else if (action == 2) hero->rageStrike(monster);
    else if (action == 3) hero->whirlwind(monster);
    else {
        if (hero->getRage() < 30) { cout << "❌ Rage tidak cukup (butuh 30).\n"; return false; }
        hero->selfHeal();
    }
    return true;
}
