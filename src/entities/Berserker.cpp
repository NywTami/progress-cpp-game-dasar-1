#include "Berserker.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

float Berserker::calculateDamageMultiplier() const {
    if (berserk_turns_remaining > 0 || rage >= 300) {
        return 2.5f;
    }

    return 1.0f + (rage / 30) * 0.1f;
}

void Berserker::gainRage(int amount) {
    if (amount <= 0 || !isAlive()) {
        return;
    }

    rage = min(max_rage, rage + amount);

    cout << nama << " mendapat +" << amount << " rage. "
         << "Rage: " << rage << "/" << max_rage << "\n";

    if (rage >= max_rage && berserk_turns_remaining == 0) {
        berserk_turns_remaining = 4;
        cout << "\n🔥 " << nama
             << " memasuki Berserk Mode! Damage x2.5 selama 4 turn!\n";
    }
}

void Berserker::terimaDamage(int damage) {
    if (damage <= 0 || !isAlive()) {
        return;
    }

    // Defense Berserker selalu 0. Damage diterima penuh.
    hp = max(0, hp - damage);

    cout << nama << " menerima " << damage
         << " damage! (Defense: 0%, Sisa HP: " << hp << "/" << max_hp << ")\n";

    // 5% damage aktual, dibulatkan ke bawah. Minimal 1 rage jika damage > 0.
    int rage_gain = max(1, damage * 5 / 100);
    gainRage(rage_gain);
}

void Berserker::serang(Entity* target) {
    basicAttack(target);
}

void Berserker::basicAttack(Entity* target) {
    if (!isAlive() || target == nullptr || !target->isAlive()) {
        return;
    }

    int damage = static_cast<int>(attack_power * calculateDamageMultiplier());

    cout << "\n⚔️ " << nama << " menebas " << target->getNama()
         << "! Damage x" << fixed << setprecision(1)
         << calculateDamageMultiplier() << "\n";
    target->terimaDamage(damage);
    gainRage(20);
}

void Berserker::rageStrike(Entity* target) {
    if (!isAlive() || target == nullptr || !target->isAlive()) {
        return;
    }

    int self_damage = max(1, max_hp * 5 / 100);
    int damage = static_cast<int>(attack_power * 1.8f * calculateDamageMultiplier());

    cout << "\n🔥 " << nama << " menggunakan Rage Strike pada "
         << target->getNama() << "!\n";
    target->terimaDamage(damage);
    hp = max(0, hp - self_damage);
    cout << nama << " kehilangan " << self_damage
         << " HP karena Rage Strike. (Sisa HP: " << hp << "/" << max_hp << ")\n";
    gainRage(25);
}

void Berserker::whirlwind(Entity* target) {
    if (!isAlive() || target == nullptr || !target->isAlive()) {
        return;
    }

    int self_damage = max(1, max_hp * 4 / 100);
    int damage = static_cast<int>(attack_power * 1.4f * calculateDamageMultiplier());

    cout << "\n💨 " << nama << " menggunakan Whirlwind pada "
         << target->getNama() << "!\n";
    target->terimaDamage(damage);
    hp = max(0, hp - self_damage);
    cout << nama << " kehilangan " << self_damage
         << " HP karena Whirlwind. (Sisa HP: " << hp << "/" << max_hp << ")\n";
    gainRage(20);
}

void Berserker::selfHeal(){
    if (hp>0 && rage >= 30){
        int heal_amount = max_hp * 10 / 100;
        pulihkanHP(heal_amount);
        rage -= 30;
        cout << "\n💖 " << nama << " menggunakan Self Heal! "
             << "Memulihkan " << heal_amount << " HP. "
             << "(Sisa HP: " << hp << "/" << max_hp
             << ", Rage: " << rage << "/" << max_rage << ")\n";
    } else if (hp <= 0){
        cout << "\n❌ " << nama << " tidak bisa menggunakan Self Heal karena sudah mati.\n";
    } else {
        cout << "\n❌ " << nama << " tidak memiliki cukup rage untuk menggunakan Self Heal.\n";
    }
}

void Berserker::updateBerserkMode() {
    if (berserk_turns_remaining <= 0) {
        return;
    }

    --berserk_turns_remaining;
    cout << nama << " Berserk Mode tersisa "
         << berserk_turns_remaining << " turn.\n";

    if (berserk_turns_remaining == 0) {
        rage = 0;
        pulihkanHP(max_hp * 10 / 100);
        cout << "💥 Berserk Mode berakhir. Rage direset ke 0.\n";
    }
}

void Berserker::displayStatus() const {
    cout << "\n=== Berserker Status ===\n"
         << "HP: " << hp << "/" << max_hp << "\n"
         << "Rage: " << rage << "/" << max_rage << "\n"
         << "Damage multiplier: x" << fixed << setprecision(1)
         << calculateDamageMultiplier() << "\n"
         << "Berserk turns: " << berserk_turns_remaining << "\n";
}
