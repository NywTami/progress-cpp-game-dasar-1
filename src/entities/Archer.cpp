#include "Archer.h"
#include <iostream>

//1
void Archer::serang(Entity* target) {
    if (arrows > 0) {
        arrows--;
        cout << "\n🏹 " << nama << " menembak " << target->getNama() << " dengan panah!\n";
        target->terimaDamage(attack_power);
    } else {
        cout << "\n🏹 " << nama << " kehabisan panah!\n";
        reloadArrows();
    }
}

//1.5
void Archer::basicAttack(Entity* target) {
    cout << "\n🏹 " << nama << " melakukan serangan biasa!\n";
    target->terimaDamage(attack_power / 2);
}

//2
void Archer::specialAttack(Entity* target) {
    if (arrows > 0) {
        if (mana >= 20) {
            arrows--;
            mana -= 20;
            cout << "\n🏹 " << nama << " Menggunakan Special Attack!\n";
            int damage = (int)(attack_power * 1.5);  // fix: explicit cast
            target->terimaDamage(damage);
        } else {
            cout << "!!!!! " << nama << " Tidak Memiliki cukup mana " << mana << "/" << max_mana << " !!!!!" << endl;
            arrows--;
            target->terimaDamage(attack_power);
        }
    } else {
        cout << "\n🏹 " << nama << " kehabisan panah!\n";
        reloadArrows();
    }
}

//3
void Archer::ultimateArrow(Entity* target) {
    if (mana >= 20) {
        mana -= 20;
        cout << "\n🏹 " << nama << " Menggunakan Ultimate Arrow!\n";
        int damage = attack_power * 3;
        target->terimaDamage(damage);
    } else {
        cout << "!!!!! " << nama << " Tidak Memiliki cukup mana " << mana << "/" << max_mana << " !!!!!" << endl;
        serang(target);
    }
}

//4
void Archer::fireArrow(Entity* target) {
    if (mana >= 10) {
        mana -= 10;
        cout << "\n🔥 " << nama << " menembakkan Fire Arrow ke " << target->getNama() << "!\n";
        int damage = attack_power + 30;
        target->terimaDamage(damage);
    } else {
        cout << "!!!!! " << nama << " Tidak Memiliki cukup mana " << mana << "/" << max_mana << " !!!!!" << endl;
        serang(target);
    }
}

//5
void Archer::lightningArrow(Entity* target) {
    if (mana >= 15) {
        mana -= 15;
        cout << "\n⚡ " << nama << " menembakkan Lightning Arrow ke " << target->getNama() << "!\n";
        int damage = attack_power + 40;
        target->terimaDamage(damage);
    } else {
        cout << "!!!!! " << nama << " Tidak Memiliki cukup mana " << mana << "/" << max_mana << " !!!!!" << endl;
        serang(target);
    }
}

//6
void Archer::poisonArrow(Entity* target) {
    if (mana >= 10) {
        mana -= 10;
        cout << "\n☠️ " << nama << " menembakkan Poison Arrow ke " << target->getNama() << "!\n";
        int damage = attack_power + 20;
        target->terimaDamage(damage);
    } else {
        cout << "!!!!! " << nama << " Tidak Memiliki cukup mana " << mana << "/" << max_mana << " !!!!!" << endl;
        serang(target);
    }
}

//7
void Archer::multiShot(Entity* target) {
    if (mana >= 25) {
        mana -= 25;
        cout << "\n🏹 " << nama << " menggunakan Multi Shot!\n";
        int damage = attack_power * 2;
        target->terimaDamage(damage);
    } else {
        cout << "!!!!! " << nama << " Tidak Memiliki cukup mana " << mana << "/" << max_mana << " !!!!!" << endl;
        serang(target);
    }
}

//8
void Archer::rapidFire(Entity* target) {
    if (mana >= 30) {
        mana -= 30;
        cout << "\n🏹 " << nama << " menggunakan Rapid Fire!\n";
        int damage = attack_power * 3;
        target->terimaDamage(damage);
    } else {
        cout << "!!!!! " << nama << " Tidak Memiliki cukup mana " << mana << "/" << max_mana << " !!!!!" << endl;
        serang(target);
    }
}

//9
void Archer::reloadArrows() {
    arrows++;
    if (arrows > max_arrows) {
        arrows = max_arrows;
    }
    cout << "\n🏹 " << nama << " mengisi ulang anak panah sebanyak 1! (Arrows: " << arrows << "/" << max_arrows << ")\n";
}

//10
void Archer::regenMana() {
    mana += 10;
    if (mana > max_mana) {
        mana = max_mana;
    }
    cout << "\n💧 " << nama << " meregenerasi 10 mana! (Mana: " << mana << "/" << max_mana << ")\n";
}