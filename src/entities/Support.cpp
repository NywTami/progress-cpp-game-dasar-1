#include "Support.h"
#include <iostream>

using namespace std;

void Support::serang(Entity* target) {
    basicAttack(target);
}

void Support::basicAttack(Entity* target) {
    cout << "\n⚔️ " << nama << " menyerang " << target->getNama()
         << " dengan tongkat!\n";
    target->terimaDamage(attack_power);
}

void Support::heal(Entity* target) {
    const int biaya_mana = 10;
    const int jumlah_heal = 30;

    if (mana < biaya_mana) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk Heal! "
             << "(Mana: " << mana << "/" << max_mana << ")\n";
        return;
    }

    mana -= biaya_mana;
    cout << "\n💚 " << nama << " menggunakan Heal pada " << target->getNama()
         << "! (Sisa Mana: " << mana << ")\n";
    target->pulihkanHP(jumlah_heal);
}

void Support::massHeal(Entity* p1, Entity* p2, Entity* p3) {
    const int biaya_mana = 25;
    const int jumlah_heal = 20;

    if (mana < biaya_mana) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk Mass Heal! "
             << "(Mana: " << mana << "/" << max_mana << ")\n";
        return;
    }

    mana -= biaya_mana;
    cout << "\n💚 " << nama << " menggunakan Mass Heal! (Sisa Mana: "
         << mana << ")\n";

    if (p1 && p1->isAlive()) p1->pulihkanHP(jumlah_heal);
    if (p2 && p2->isAlive()) p2->pulihkanHP(jumlah_heal);
    if (p3 && p3->isAlive()) p3->pulihkanHP(jumlah_heal);
}

void Support::regenMana(int amount) {
    mana += amount;
    if (mana > max_mana) {
        mana = max_mana;
    }

    cout << "\n✨ " << nama << " regenerasi mana +" << amount
         << " (Mana: " << mana << "/" << max_mana << ")\n";
}

void Support::buffDefense(Entity* target) {
    const int biaya_mana = 15;
    const int buff_value = 10;

    if (mana < biaya_mana) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk Buff Defense! "
             << "(Mana: " << mana << "/" << max_mana << ")\n";
        return;
    }

    mana -= biaya_mana;
    target->tambahDefense(buff_value);
    cout << "\n✨ " << nama << " menggunakan Buff Defense pada "
         << target->getNama() << "! (Sisa Mana: " << mana << "/" << max_mana << ")\n";
}

void Support::buffAttackPower(Entity* target) {
    const int biaya_mana = 20;
    const int buff_percent = 30;  // +30% attack

    if (mana < biaya_mana) {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk Buff Attack Power! "
             << "(Mana: " << mana << "/" << max_mana << ")\n";
        return;
    }

    mana -= biaya_mana;
    int buff_amount = (target->getAttackPower() * buff_percent) / 100;
    target->tambahDefense(buff_amount);  // TODO: Need buffAttackPower method in Entity
    cout << "\n✨ " << nama << " menggunakan Buff Attack Power pada "
         << target->getNama() << "! (Sisa Mana: " << mana << "/" << max_mana << ")\n";
}