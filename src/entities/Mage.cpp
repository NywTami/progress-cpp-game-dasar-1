#include "Mage.h"
#include <iostream>

void Mage::serang(Entity* target) {
    cout << "\n⚔️ " << nama << " menyerang " << target->getNama() << " dengan Staff!\n";
    target->terimaDamage(attack_power);
}

void Mage::basicAttack(Entity* target) {
    cout << "\n⚔️ " << nama << " menyerang " << target->getNama() << " dengan Pedang!\n";
    target->terimaDamage(attack_power);
}

void Mage::fireball(Entity* target) {
    if (mana >= 10) {
        mana -= 10;
        int damage_skill = attack_power + 15;
        cout << "\n🔥 " << nama << " menggunakan Skill Kritis [Fireball]! (Sisa Mana: " << mana << ")\n";
        target->terimaDamage(damage_skill);
    } else {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk menggunakan Fireball! (Sisa Mana: " << mana << ")\n";
        basicAttack(target);
    }
}

void Mage::ultimateBurst(Entity* target) {
    if (mana >= 20) {
        mana -= 20;
        int damage_skill = attack_power * 2;
        cout << "\n🔥 " << nama << " menggunakan Skill Kritis [Ultimate Burst]! (Sisa Mana: " << mana << ")\n";
        target->terimaDamage(damage_skill);
    } else {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk menggunakan Ultimate Burst! (Sisa Mana: " << mana << ")\n";
        basicAttack(target);
    }
}

void Mage::regenMana(int amount) {
    mana += amount;
    if (mana > max_mana) {
        mana = max_mana;
    }
    cout << "\n✨ " << nama << " regenerasi mana +" << amount << " (Mana: " << mana << "/" << max_mana << ")\n";
}


