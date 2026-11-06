#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <limits>
#include "Progression.h"
#include "entities/Support.h"
#include "entities/Knight.h"
#include "entities/Archer.h"
#include "entities/Mage.h"
#include "entities/Hunter.h"
#include "entities/Berserker.h"
#include "entities/Monster.h"

using namespace std;

// Forward declarations
void executeHeroTurn(Entity* hero, Entity* monster, vector<Entity*>& active_roster);
void executeMonsterTurn(Entity* monster, vector<Entity*>& active_roster);
void displayBattleStatus(const vector<Entity*>& active_roster, Entity* monster);

void executeHeroTurn(Entity* hero, Entity* monster, vector<Entity*>& active_roster) {
    cout << "\n⚔️  Giliran " << hero->getNama() << "\n";
    cout << "HP: " << hero->getHP() << "/" << hero->getMaxHP() << "\n";
    
    // Determine hero type and display appropriate menu
    Support* support = dynamic_cast<Support*>(hero);
    Knight* knight = dynamic_cast<Knight*>(hero);
    Archer* archer = dynamic_cast<Archer*>(hero);
    Mage* mage = dynamic_cast<Mage*>(hero);
    Hunter* hunter = dynamic_cast<Hunter*>(hero);
    Berserker* berserker = dynamic_cast<Berserker*>(hero);
    
    int aksi = -1;
    bool valid = false;
    
    if (support) {
        cout << "Mana: " << support->getMana() << "/" << support->getMaxMana() << "\n";
        cout << "\n1. Basic Attack\n";
        cout << "2. Heal (10 mana)\n";
        cout << "3. Mass Heal (25 mana)\n";
        cout << "4. Regen Mana\n";
        cout << "5. Buff Defense (15 mana)\n";
        cout << "6. Buff Attack Power (15 mana)\n";
        cout << "Pilihan: ";
        
        if (!(cin >> aksi) || aksi < 1 || aksi > 6) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "❌ Aksi tidak valid. Giliran terlewat.\n";
            return;
        }
        
        if (aksi == 1) {
            support->serang(monster);
            valid = true;
        } else if (aksi == 2) {
            cout << "\nPilih target heal (1-" << active_roster.size() << "): ";
            int target_idx;
            if (cin >> target_idx && target_idx >= 1 && target_idx <= active_roster.size()) {
                support->heal(active_roster[target_idx - 1]);
                valid = true;
            } else {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "❌ Target tidak valid.\n";
            }
        } else if (aksi == 3) {
            support->massHeal(active_roster[0], active_roster.size() > 1 ? active_roster[1] : nullptr, 
                            active_roster.size() > 2 ? active_roster[2] : nullptr);
            valid = true;
        } else if (aksi == 4) {
            support->regenMana(15);
            valid = true;
        }
    } else if (knight) {
        cout << "Faith: " << knight->getFaith() << "/" << knight->getMaxfaith() << "\n";
        cout << "\n1. Basic Attack\n";
        cout << "2. Power Strike\n";
        cout << "3. Ultimate Charge\n";
        cout << "4. Shield Block (20 faith)\n";
        cout << "5. Regen Faith\n";
        cout << "6. Bless Defense (15 faith)\n";
        cout << "Pilihan: ";
        
        if (!(cin >> aksi) || aksi < 1 || aksi > 6) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "❌ Aksi tidak valid. Giliran terlewat.\n";
            return;
        }
        
        if (aksi == 1) {
            knight->serang(monster);
            valid = true;
        } else if (aksi == 2) {
            knight->powerStrike(monster);
            valid = true;
        } else if (aksi == 3) {
            knight->ultimateCharge(monster);
            valid = true;
        } else if (aksi == 4) {
            knight->shieldBlock();
            valid = true;
        } else if (aksi == 5) {
            knight->regenFaith();
            valid = true;
        } else if (aksi == 6) {
            cout << "\nPilih target bless (1-" << active_roster.size() << "): ";
            int target_idx;
            if (cin >> target_idx && target_idx >= 1 && target_idx <= active_roster.size()) {
                knight->blessDefense(active_roster[target_idx - 1]);
                valid = true;
            } else {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "❌ Target tidak valid.\n";
            }
        }
    } else if (archer) {
        cout << "Arrows: " << archer->getArrows() << "/" << archer->getMaxarrows() 
             << ", Mana: " << archer->getMana() << "/" << archer->getMaxmana() << "\n";
        cout << "\n1. Basic Attack\n";
        cout << "2. Basic Attack (tanpa panah)\n";
        cout << "3. Special Attack (20 mana, 1 panah)\n";
        cout << "4. Reload Arrows\n";
        cout << "5. Fire Arrow (10 mana)\n";
        cout << "6. Lightning Arrow (15 mana)\n";
        cout << "7. Poison Arrow (15 mana)\n";
        cout << "8. Multi Shot (25 mana, 3 panah)\n";
        cout << "9. Rapid Fire (30 mana, 5 panah)\n";
        cout << "10. Regen Mana\n";
        cout << "Pilihan: ";
        
        if (!(cin >> aksi) || aksi < 1 || aksi > 10) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "❌ Aksi tidak valid. Giliran terlewat.\n";
            return;
        }
        
        if (aksi == 1) {
            archer->serang(monster);
            valid = true;
        } else if (aksi == 2) {
            archer->basicAttack(monster);
            valid = true;
        } else if (aksi == 3) {
            archer->specialAttack(monster);
            valid = true;
        } else if (aksi == 4) {
            archer->reloadArrows();
            valid = true;
        } else if (aksi == 5) {
            archer->fireArrow(monster);
            valid = true;
        } else if (aksi == 6) {
            archer->lightningArrow(monster);
            valid = true;
        } else if (aksi == 7) {
            archer->poisonArrow(monster);
            valid = true;
        } else if (aksi == 8) {
            archer->multiShot(monster);
            valid = true;
        } else if (aksi == 9) {
            archer->rapidFire(monster);
            valid = true;
        } else if (aksi == 10) {
            archer->regenMana();
            valid = true;
        }
    } else if (mage) {
        cout << "Mana: " << mage->getMana() << "/" << mage->getMaxmana() << "\n";
        cout << "\n1. Basic Attack\n";
        cout << "2. Fireball (15 mana)\n";
        cout << "3. Ultimate Burst (30 mana)\n";
        cout << "4. Regen Mana\n";
        cout << "Pilihan: ";
        
        if (!(cin >> aksi) || aksi < 1 || aksi > 4) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "❌ Aksi tidak valid. Giliran terlewat.\n";
            return;
        }
        
        if (aksi == 1) {
            mage->serang(monster);
            valid = true;
        } else if (aksi == 2) {
            mage->fireball(monster);
            valid = true;
        } else if (aksi == 3) {
            mage->ultimateBurst(monster);
            valid = true;
        } else if (aksi == 4) {
            mage->regenMana(20);
            valid = true;
        }
    } else if (hunter) {
        cout << "Energy: " << hunter->getEnergy() << "/" << hunter->getMaxEnergy() << "\n";
        cout << "\n1. Basic Attack\n";
        cout << "2. Power Shot (20 energy)\n";
        cout << "3. Beast Companion (25 energy)\n";
        cout << "4. Tracking Shot (15 energy)\n";
        cout << "5. Disadvantage Shot (20 energy)\n";
        cout << "6. Hunter's Mark (10 energy)\n";
        cout << "7. Regen Energy\n";
        cout << "Pilihan: ";
        
        if (!(cin >> aksi) || aksi < 1 || aksi > 7) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "❌ Aksi tidak valid. Giliran terlewat.\n";
            return;
        }
        
        if (aksi == 1) {
            hunter->serang(monster);
            valid = true;
        } else if (aksi == 2) {
            if (hunter->getEnergy() < 20) {
                cout << "❌ Energy tidak cukup. Pilih Regen Energy atau skill lain.\n";
                return;
            }
            hunter->powerShot(monster);
            valid = true;
        } else if (aksi == 3) {
            if (hunter->getEnergy() < 25) {
                cout << "❌ Energy tidak cukup. Pilih Regen Energy atau skill lain.\n";
                return;
            }
            hunter->beastCompanion(monster);
            valid = true;
        } else if (aksi == 4) {
            if (hunter->getEnergy() < 15) {
                cout << "❌ Energy tidak cukup. Pilih Regen Energy atau skill lain.\n";
                return;
            }
            hunter->trackingShot(monster);
            valid = true;
        } else if (aksi == 5) {
            if (hunter->getEnergy() < 20) {
                cout << "❌ Energy tidak cukup. Pilih Regen Energy atau skill lain.\n";
                return;
            }
            hunter->disadvantageShot(monster);
            valid = true;
        } else if (aksi == 6) {
            if (hunter->getEnergy() < 10) {
                cout << "❌ Energy tidak cukup. Pilih Regen Energy atau skill lain.\n";
                return;
            }
            hunter->huntersMark(monster);
            valid = true;
        } else if (aksi == 7) {
            hunter->regenEnergy(20);
            valid = true;
        }
    } else if (berserker) {
        cout << "Rage: " << berserker->getRage() << "/" << berserker->getMaxRage() << "\n";
        cout << "\n1. Basic Attack\n";
        cout << "2. Rage Strike\n";
        cout << "3. Whirlwind\n";
        cout << "4. Self Heal\n";
        cout << "Pilihan: ";
        
        if (!(cin >> aksi) || aksi < 1 || aksi > 4) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "❌ Aksi tidak valid. Giliran terlewat.\n";
            return;
        }
        
        if (aksi == 1) {
            berserker->serang(monster);
            valid = true;
        } else if (aksi == 2) {
            berserker->rageStrike(monster);
            valid = true;
        } else if (aksi == 3) {
            berserker->whirlwind(monster);
            valid = true;
        } else if (aksi == 4) {
            berserker->selfHeal();
            valid = true;
        }
    }
    
    if (!valid) {
        cout << "❌ Aksi tidak valid. Giliran terlewat.\n";
    }
}

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
    cout << "Hero 0: " << active_roster[0]->getNama() << "\n";
    cout << "Hero 1: " << active_roster[1]->getNama() << "\n";
    cout << "Hero 2: " << active_roster[2]->getNama() << "\n";
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
