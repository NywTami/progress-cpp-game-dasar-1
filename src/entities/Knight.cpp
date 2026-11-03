#include "Knight.h"
#include <iostream>

void Knight::serang(Entity* target) {
    cout << "\n🛡️ " << nama << " menyerang " << target->getNama() << " dengan Pedang!\n";
    target->terimaDamage(attack_power);
}

void Knight::regenFaith() {
    faith += 20;
    if (faith > max_faith) {
        faith = max_faith;
    }
    cout << "\n🛡️ " << nama << " Menggunakan Regen Faith, Faith + 20 (Faith: " << faith << "/" << max_faith << ")\n";
}

void Knight::shieldBlock() {
    if (faith >= 20) {
        faith -= 20;
        cout << "\n🛡️ " << nama << " menggunakan Shield Block untuk meningkatkan pertahanan!\n";
        defense += 10;
    } else {
        cout << "Tidak Memiliki cukup Faith! (Faith : " << faith << ")\n";
        cout << "Mengcast Regen Faith\n";
        regenFaith();
    }
}

void Knight::powerStrike(Entity* target) {
    cout << "\n⚔️ " << nama << " menggunakan Power Strike!\n";
    int damage = attack_power + 20;
    target->terimaDamage(damage);
}

void Knight::ultimateCharge(Entity* target) {
    cout << "\n⚡ " << nama << " menggunakan Ultimate Charge!\n";
    int damage = attack_power * 2;
    target->terimaDamage(damage);
}

void Knight::blessDefense(Entity* target) {
    if (faith >= 15) {
        faith -= 15;
        cout << "\n✨ " << nama << " menggunakan Bless Defense pada " << target->getNama() << "! (Sisa Faith: " << faith << ")\n";
        target->tambahDefense(15);
    } else {
        cout << "\n⚠️ " << nama << " tidak memiliki cukup Faith untuk Bless Defense! (Sisa Faith: " << faith << ")\n";
        regenFaith();
    }
}
