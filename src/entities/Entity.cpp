#include "Entity.h"
#include <iostream>

void Entity::terimaDamage(int damage) {
    double persen_reduksi = defense / 10.0;

    if (persen_reduksi > 100.0) {
        persen_reduksi = 100.0;
    } else if (persen_reduksi < 0.0) {
        persen_reduksi = 0.0;
    }

    int actual_damage = damage * (100.0 - persen_reduksi) / 100.0;

    hp -= actual_damage;

    if (hp < 0) {
        hp = 0;
    }

    cout << nama << " menerima " << actual_damage
         << " damage! (Defense: " << persen_reduksi
         << "%, Sisa HP: " << hp << "/" << max_hp << ")\n";
}

void Entity::pulihkanHP(int amount) {
    if (!isAlive() || amount <= 0) {
        return;
    }

    hp += amount;
    if (hp > max_hp) {
        hp = max_hp;
    }

    cout << nama << " memulihkan HP sebanyak " << amount
         << "! (Sisa HP: " << hp << "/" << max_hp << ")\n";
}

void Entity::tambahDefense(int amount) {
    defense += amount;
    cout << nama << " mendapat buff defense +" << amount
         << "! (Defense: " << defense << ")\n";
}

void Entity::resetDefense(int original_defense) {
    defense = original_defense;
    cout << nama << " buff defense hilang. (Defense: " << defense << ")\n";
}

void Entity::gainExp(int amount) {
    exp += amount;
    cout << nama << " mendapat " << amount << " exp!\n";
    if (exp >= max_exp) {
        levelUp();
    }
}

void Entity::levelUp() {
    level++;
    exp = 0;
    max_exp = level * 100;
    attack_power += 5;
    defense += 3;
    hp += 20;
    max_hp = hp;
    cout << "\n⭐ " << nama << " naik level ke " << level << "!\n";
    cout << "Attack: +" << 5 << ", Defense: +" << 3 << ", HP: +" << 20 << "\n";
}
