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
    
    // Deal damage
    int beast_damage = attack_power * 80 / 100;
    target->terimaDamage(beast_damage);
    
    // Add 1 stack ONLY if Prey is already active
    if (target->getPreyStackCount() > 0) {
        StatusPreyMark stack_bonus("Prey", EffectType::Debuff, TargetStat::DefensePercent, 1, 10, 0, true);
        target->applyPreyMark(stack_bonus);
        cout << "  ➕ Prey stacks +1\n";
    } else {
        cout << "  ℹ️ Target tidak memiliki Prey Mark. Stacks tidak ditambah.\n";
    }
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
    
    int tracking_damage = attack_power * 120 / 100;
    target->terimaDamage(tracking_damage);
}


void Hunter::disadvantageShot(Entity* target) {
    const int biaya_energy = 20;
    
    if (energy < biaya_energy) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup energy untuk Disadvantage Shot! "
             << "(Energy: " << energy << "/" << max_energy << ")\n";
        return;
    }

    energy -= biaya_energy;
    cout << "\n🔻 " << nama << " melepas disadvantage shot pada " << target->getNama() 
         << "! (Sisa Energy: " << energy << "/" << max_energy << ")\n";
    
    // Deal damage
    int damage = attack_power * 130 / 100;
    target->terimaDamage(damage);
    
    // Add 2 stacks ONLY if Prey is already active
    if (target->getPreyStackCount() > 0) {
        StatusPreyMark stack_bonus("Prey", EffectType::Debuff, TargetStat::DefensePercent, 2, 10, 0, true);
        target->applyPreyMark(stack_bonus);
        cout << "  ➕ Prey stacks +2\n";
    } else {
        cout << "  ℹ️ Target tidak memiliki Prey Mark. Stacks tidak ditambah.\n";
    }
}

void Hunter::huntersMark(Entity* target) {
    const int biaya_energy = 10;
    
    if (energy < biaya_energy) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup energy untuk Hunter's Mark! "
             << "(Energy: " << energy << "/" << max_energy << ")\n";
        return;
    }

    energy -= biaya_energy;
    cout << "\n🎯 " << nama << " melepas Hunter's Mark pada " << target->getNama() 
         << "! (Sisa Energy: " << energy << "/" << max_energy << ")\n";
    
    // Check if target already has Prey Mark
    if (target->getPreyStackCount() == 0) {
        // First application: 5 stacks
        StatusPreyMark prey_mark("Prey", EffectType::Debuff, TargetStat::DefensePercent, 5, 10, 4, true);
        target->applyPreyMark(prey_mark);
    } else {
        // Already has Prey: add 1 stack and reset duration
        StatusPreyMark prey_refresh("Prey", EffectType::Debuff, TargetStat::DefensePercent, 1, 10, 4, true);
        target->applyPreyMark(prey_refresh);
    }
}

void Hunter::regenEnergy(int amount) {
    energy += amount;
    if (energy > max_energy) {
        energy = max_energy;
    }

    cout << "\n⚡ " << nama << " mengisi ulang energy +" << amount
         << " (Energy: " << energy << "/" << max_energy << ")\n";
}
