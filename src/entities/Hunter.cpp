#include "Hunter.h"
#include <iostream>

using namespace std;

void Hunter::serang(Entity* target) {
    basicAttack(target);
}

void Hunter::basicAttack(Entity* target) {
    cout << "\n🏹 " << nama << " melepas panah pada " << target->getNama() << "!\n";
    target->terimaDamage(attack_power);
}

void Hunter::powerShot(Entity* target) {
    const int biaya_energy = 20;
    
    if (energy < biaya_energy) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup energy untuk Power Shot! "
             << "(Energy: " << energy << "/" << max_energy << ")\n";
        return;
    }

    energy -= biaya_energy;
    cout << "\n💣 " << nama << " melepas power shot pada " << target->getNama() 
         << "! (Sisa Energy: " << energy << "/" << max_energy << ")\n";
    
    int power_damage = attack_power * 150 / 100;
    target->terimaDamage(power_damage);
}

void Hunter::beastCompanion(Entity* target) {
    const int biaya_energy = 25;
    
    if (energy < biaya_energy) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup energy untuk Beast Companion! "
             << "(Energy: " << energy << "/" << max_energy << ")\n";
        return;
    }

    if (pet_health <= 0) {
        cout << "\n⚠️ Companion pet sudah mati! Tidak bisa dipanggil.\n";
        return;
    }

    energy -= biaya_energy;
    cout << "\n🐺 " << nama << " memanggil beast companion untuk menyerang " << target->getNama() 
         << "! (Sisa Energy: " << energy << "/" << max_energy << ")\n";
    
    int beast_damage = attack_power * 80 / 100;
    target->terimaDamage(beast_damage);
}

void Hunter::trackingShot(Entity* target) {
    const int biaya_energy = 15;
    
    if (energy < biaya_energy) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup energy untuk Tracking Shot! "
             << "(Energy: " << energy << "/" << max_energy << ")\n";
        return;
    }

    energy -= biaya_energy;
    cout << "\n🎯 " << nama << " melepas tracking shot pada " << target->getNama() 
         << "! (Sisa Energy: " << energy << "/" << max_energy << ")\n";
    
    int tracking_damage = attack_power * 100 / 100;
    target->terimaDamage(tracking_damage);
    
    // Apply debuff: reduce enemy attack power for 2 turns
    StatusEffect debuff("Tracked", EffectType::Debuff, TargetStat::AttackPercent, 20, 2);
    target->applyEffect(debuff);
}

void Hunter::focusShot(Entity* target) {
    const int biaya_focus = 30;
    
    if (focus < biaya_focus) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup focus untuk Focus Shot! "
             << "(Focus: " << focus << "/" << max_focus << ")\n";
        return;
    }

    focus -= biaya_focus;
    cout << "\n🎯 " << nama << " melepas focus shot pada " << target->getNama() 
         << "! (Sisa Focus: " << focus << "/" << max_focus << ")\n";
    
    int focus_damage = attack_power * 200 / 100;
    target->terimaDamage(focus_damage);
}

void Hunter::disadvantageShot(Entity* target) {
    const int biaya_focus = 20;
    
    if (focus < biaya_focus) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup focus untuk Disadvantage Shot! "
             << "(Focus: " << focus << "/" << max_focus << ")\n";
        return;
    }

    focus -= biaya_focus;
    cout << "\n🔻 " << nama << " melepas disadvantage shot pada " << target->getNama() 
         << "! (Sisa Focus: " << focus << "/" << max_focus << ")\n";
    
    // Apply debuff: reduce enemy defense for 3 turns
    StatusEffect debuff("Disadvantaged", EffectType::Debuff, TargetStat::DefensePoints, 15, 3);
    target->applyEffect(debuff);
}

void Hunter::huntersMark(Entity* target) {
    const int biaya_focus = 25;
    
    if (focus < biaya_focus) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup focus untuk Hunter's Mark! "
             << "(Focus: " << focus << "/" << max_focus << ")\n";
        return;
    }

    focus -= biaya_focus;
    cout << "\n🔖 " << nama << " menandai " << target->getNama() 
         << " dengan Hunter's Mark! (Sisa Focus: " << focus << "/" << max_focus << ")\n";
    
    // Apply debuff: increase damage taken by enemy for 4 turns
    StatusEffect debuff("Marked", EffectType::Debuff, TargetStat::DefensePoints, 20, 4);
    target->applyEffect(debuff);
}

void Hunter::regenEnergy(int amount) {
    energy += amount;
    if (energy > max_energy) {
        energy = max_energy;
    }

    cout << "\n⚡ " << nama << " mengisi ulang energy +" << amount
         << " (Energy: " << energy << "/" << max_energy << ")\n";
}
