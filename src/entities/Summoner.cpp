#include "Summoner.h"
#include <iostream>

using namespace std;

void Summoner::serang(Entity* target) {
    basicAttack(target);
}

void Summoner::basicAttack(Entity* target) {
    cout << "\n⚔️ " << nama << " melempar sihir dasar pada " << target->getNama() << "!\n";
    int damage = attack_power / 2;  // Summoner basic attack weaker, relies on summons
    target->terimaDamage(damage);
}

void Summoner::summonAlly(Entity* target) {
    const int biaya_mana = 30;
    
    if (mana < biaya_mana) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk Summon Ally! "
             << "(Mana: " << mana << "/" << max_mana << ")\n";
        return;
    }

    mana -= biaya_mana;
    summon_count++;
    
    cout << "\n✨ " << nama << " memanggil sekutu magical! Summon ke-" << summon_count 
         << " (Sisa Mana: " << mana << "/" << max_mana << ")\n";
    
    // Summon deals damage
    int summon_damage = attack_power * 60 / 100;
    cout << "🐉 Sekutu menyerang " << target->getNama() << "!\n";
    target->terimaDamage(summon_damage);
}

void Summoner::arcaneBurst(Entity* target) {
    const int biaya_mana = 25;
    
    if (mana < biaya_mana) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk Arcane Burst! "
             << "(Mana: " << mana << "/" << max_mana << ")\n";
        return;
    }

    mana -= biaya_mana;
    cout << "\n💥 " << nama << " mengeluarkan ledakan sihir pada " << target->getNama() 
         << "! (Sisa Mana: " << mana << "/" << max_mana << ")\n";
    
    int arcane_damage = attack_power * 120 / 100;
    target->terimaDamage(arcane_damage);
}

void Summoner::manaShield() {
    const int biaya_mana = 15;
    
    if (mana < biaya_mana) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk Mana Shield! "
             << "(Mana: " << mana << "/" << max_mana << ")\n";
        return;
    }

    mana -= biaya_mana;
    cout << "\n🛡️ " << nama << " menciptakan perisai sihir! Defense terlindungi sementara. "
         << "(Sisa Mana: " << mana << "/" << max_mana << ")\n";
    
    // Temporary defense buff (duration 3 turns)
    StatusEffect shield("Mana Shield", EffectType::Buff, TargetStat::DefensePoints, 20, 3);
    applyEffect(shield);
}

void Summoner::regenMana(int amount) {
    mana += amount;
    if (mana > max_mana) {
        mana = max_mana;
    }

    cout << "\n✨ " << nama << " regenerasi mana +" << amount
         << " (Mana: " << mana << "/" << max_mana << ")\n";
}
