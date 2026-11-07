#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "Progression.h"
#include "battle/HeroTurn.h"
#include "entities/Support.h"
#include "entities/Knight.h"
#include "entities/Archer.h"
#include "entities/Mage.h"
#include "entities/Hunter.h"
#include "entities/Berserker.h"
#include "entities/Monster.h"

using namespace std;

void executeMonsterTurn(Entity* monster, vector<Entity*>& active_roster) {
    if (!monster->isAlive() || active_roster.empty()) return;
    
    cout << "\n👹 Giliran Monster: " << monster->getNama() << "\n";
    
    // AI: random target dari hero yang masih hidup
    vector<Entity*> alive_heroes;
    for (auto hero : active_roster) {
        if (hero->isAlive()) {
            alive_heroes.push_back(hero);
        }
    }
    
    if (!alive_heroes.empty()) {
        int target_idx = rand() % alive_heroes.size();
        monster->serang(alive_heroes[target_idx]);
    }
}

void displayBattleStatus(const vector<Entity*>& active_roster, Entity* monster) {
    cout << "\n--- Status ---\n";
    for (size_t i = 0; i < active_roster.size(); i++) {
        Entity* hero = active_roster[i];
        if (!hero) continue;
        
        cout << (i + 1) << ". " << hero->getNama() 
             << " - HP: " << hero->getHP() << "/" << hero->getMaxHP();
        
        Support* support = dynamic_cast<Support*>(hero);
        Knight* knight = dynamic_cast<Knight*>(hero);
        Archer* archer = dynamic_cast<Archer*>(hero);
        Mage* mage = dynamic_cast<Mage*>(hero);
        Hunter* hunter = dynamic_cast<Hunter*>(hero);
        Berserker* berserker = dynamic_cast<Berserker*>(hero);
        
        if (support) cout << " | Mana: " << support->getMana() << "/" << support->getMaxMana();
        else if (knight) cout << " | Faith: " << knight->getFaith() << "/" << knight->getMaxfaith();
        else if (archer) cout << " | Arrows: " << archer->getArrows() << "/" << archer->getMaxarrows();
        else if (mage) cout << " | Mana: " << mage->getMana() << "/" << mage->getMaxmana();
        else if (hunter) cout << " | Energy: " << hunter->getEnergy() << "/" << hunter->getMaxEnergy();
        else if (berserker) cout << " | Rage: " << berserker->getRage() << "/" << berserker->getMaxRage();
        
        if (hero->getPreyStackCount() > 0) {
            cout << " | 🎯 Prey: " << hero->getPreyStackCount() << "/10";
        }
        
        cout << "\n";
    }
    
    cout << "Monster: " << monster->getNama() << " - HP: " << monster->getHP() << "/" << monster->getMaxHP();
    if (monster->getPreyStackCount() > 0) {
        cout << " | 🎯 Prey: " << monster->getPreyStackCount() << "/10";
    }
    cout << "\n";
}

int main() {
    srand(time(0));
    
    cout << "===============================================================================================\n";
    cout << "==========               Selamat datang di Game Pertarungan!               ==========\n";
    cout << "===============================================================================================\n\n";
    
    // Hero Selection
    vector<Entity*> active_roster = Progression::displayHeroSelectionMenu();
    
    if (active_roster.size() != 3) {
        cout << "❌ Gagal membuat 3 hero. Game dihentikan.\n";
        for (auto hero : active_roster) delete hero;
        return 1;
    }
    
    // Create monster
    Monster* monster = new Monster("Goblin Boss", 300, 300, 35, 15);
    
    cout << "\n=== PERTARUNGAN DIMULAI ===\n";
    cout << "Hero 1: " << active_roster[0]->getNama() << "\n";
    cout << "Hero 2: " << active_roster[1]->getNama() << "\n";
    cout << "Hero 3: " << active_roster[2]->getNama() << "\n";
    cout << "VS\n";
    cout << "Monster: " << monster->getNama() << "\n";
    cout << "============================\n\n";
    
    int turn = 1;
    while (true) {
        cout << "\n--- Turn " << turn << " ---\n";
        displayBattleStatus(active_roster, monster);
        
        // Hero turns
        for (size_t i = 0; i < active_roster.size(); i++) {
            Entity* hero = active_roster[i];
            
            if (!hero || !hero->isAlive()) {
                if (hero) {
                    cout << "\n❌ " << hero->getNama() << " tidak dapat bertindak (gugur).\n";
                }
                continue;
            }
            
            executeHeroTurn(hero, monster, active_roster);
            hero->updateEffects();
            
            if (!monster->isAlive()) {
                cout << "\n🎉 " << monster->getNama() << " telah dikalahkan!\n";
                goto battle_end;
            }
        }
        
        // Monster turn
        if (monster->isAlive()) {
            executeMonsterTurn(monster, active_roster);
            monster->updateEffects();
        }
        
        // Remove dead heroes from roster
        auto it = active_roster.begin();
        while (it != active_roster.end()) {
            if (!(*it)->isAlive()) {
                cout << "\n💀 " << (*it)->getNama() << " telah gugur!\n";
                it = active_roster.erase(it);
            } else {
                ++it;
            }
        }
        
        // Check win/loss
        if (active_roster.empty()) {
            cout << "\n💀 Semua hero telah gugur! Monster menang!\n";
            goto battle_end;
        }
        
        if (!monster->isAlive()) {
            cout << "\n🎉 Monster telah dikalahkan! Pemain menang!\n";
            goto battle_end;
        }
        
        cout << "\n===============================================================================================\n";
        turn++;
    }
    
    battle_end:
    cout << "\n=== PERTARUNGAN SELESAI ===\n";
    cout << "Total turn: " << turn << "\n";
    cout << "Monster HP: " << monster->getHP() << "/" << monster->getMaxHP() << "\n";
    cout << "\nHero Status Akhir:\n";
    for (auto hero : active_roster) {
        cout << "- " << hero->getNama() << " HP: " << hero->getHP() << "/" << hero->getMaxHP() << "\n";
    }
    cout << "============================\n";
    
    // Cleanup
    for (auto hero : active_roster) delete hero;
    delete monster;
    
    return 0;
}
