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

void Hunter::regenEnergy(int amount) {
    energy += amount;
    if (energy > max_energy) {
        energy = max_energy;
    }

    cout << "\n⚡ " << nama << " mengisi ulang energy +" << amount
         << " (Energy: " << energy << "/" << max_energy << ")\n";
}
