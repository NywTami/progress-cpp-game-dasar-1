#include "Progression.h"
#include "HeroRoster.h"
#include <iostream>
#include <limits>

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

vector<Entity*> Progression::displayHeroSelectionMenu() {
    vector<Entity*> roster;
    
    cout << "\n===============================================================================================\n";
    cout << "==========                    Pemilihan 3 Hero Pertarungan                     ==========\n";
    cout << "===============================================================================================\n\n";
    
    cout << "=== Daftar Hero Tersedia ===\n";
    for (int i = 0; i < HeroRoster::HERO_COUNT; i++) {
        const auto& spec = HeroRoster::HERO_SPECS[i];
        cout << i << ". " << spec.name 
             << " | HP: " << spec.max_hp 
             << " | ATK: " << spec.attack 
             << " | DEF: " << spec.defense 
             << " | Resource: " << spec.primary_resource << "\n";
    }
    cout << "\n";
    
    for (int slot = 1; slot <= 3; slot++) {
        int hero_choice = -1;
        bool valid = false;
        
        while (!valid) {
            cout << "Pilih Hero " << slot << " (0-" << (HeroRoster::HERO_COUNT - 1) << "): ";
            
            if (!(cin >> hero_choice)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Input tidak valid. Masukkan angka.\n";
                continue;
            }
            
            if (hero_choice >= 0 && hero_choice < HeroRoster::HERO_COUNT) {
                valid = true;
            } else {
                cout << "Pilihan tidak valid. Masukkan 0-" << (HeroRoster::HERO_COUNT - 1) << ".\n";
            }
        }
        
        Entity* hero = HeroRoster::createHero(hero_choice, "");
        if (hero) {
            roster.push_back(hero);
            cout << "✅ " << HeroRoster::HERO_SPECS[hero_choice].name << " ditambahkan ke roster.\n\n";
        } else {
            cout << "⚠️  Gagal membuat hero. Coba lagi.\n";
            slot--;
        }
    }
    
    return roster;
}
