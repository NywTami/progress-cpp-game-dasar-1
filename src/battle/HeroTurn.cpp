#include "HeroTurn.h"
#include "HeroBattle.h"

#include <iostream>

#include "entities/Support.h"
#include "entities/Knight.h"
#include "entities/Archer.h"
#include "entities/Mage.h"
#include "entities/Hunter.h"
#include "entities/Berserker.h"

using namespace std;

void executeHeroTurn(Entity* hero, Entity* monster, vector<Entity*>& active_roster) {
    bool valid = false;

    while (!valid) {
        if (auto* support = dynamic_cast<Support*>(hero)) {
            valid = executeSupportBattle(hero, monster, active_roster);
        } else if (auto* knight = dynamic_cast<Knight*>(hero)) {
            valid = executeKnightBattle(hero, monster, active_roster);
        } else if (auto* archer = dynamic_cast<Archer*>(hero)) {
            valid = executeArcherBattle(hero, monster, active_roster);
        } else if (auto* mage = dynamic_cast<Mage*>(hero)) {
            valid = executeMageBattle(hero, monster, active_roster);
        } else if (auto* hunter = dynamic_cast<Hunter*>(hero)) {
            valid = executeHunterBattle(hero, monster, active_roster);
        } else if (auto* berserker = dynamic_cast<Berserker*>(hero)) {
            valid = executeBerserkerBattle(hero, monster, active_roster);
        } else {
            cout << "❌ Hero type tidak dikenali.\n";
            return;
        }
    }
}
