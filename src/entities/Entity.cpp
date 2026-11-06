#include "Entity.h"
#include <iostream>
#include <algorithm>

void Entity::terimaDamage(int damage) {
    double persen_reduksi = defense / 10.0;
    
    // Prey lowers target defense by 6 percentage points per stack.
    if (active_prey_mark) {
        persen_reduksi -= active_prey_mark->stacks * 6.0;
    }

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

void Entity::tambahAttackPower(int amount) {
    attack_power += amount;
    cout << nama << " mendapat buff attack +" << amount
         << "! (Attack: " << attack_power << ")\n";
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

void Entity::applyEffect(const StatusEffect& effect) {
    active_effects.push_back(effect);
    cout << "\n✨ " << nama << " terkena efek: " << effect.name
         << " (durasi: " << effect.remaining_turns << " turn)\n";
}

void Entity::removeEffect(const string& effect_name) {
    auto it = active_effects.begin();
    while (it != active_effects.end()) {
        if (it->name == effect_name) {
            cout << "\n🚫 " << nama << " efek " << effect_name << " dihilangkan.\n";
            it = active_effects.erase(it);
        } else {
            ++it;
        }
    }
}

void Entity::updateEffects() {
    for (auto& effect : active_effects) {
        effect.remaining_turns--;
    }

    auto it = active_effects.begin();
    while (it != active_effects.end()) {
        if (it->remaining_turns <= 0) {
            cout << "\n⏰ " << nama << " efek " << it->name << " berakhir.\n";
            it = active_effects.erase(it);
        } else {
            ++it;
        }
    }

    updatePreyMarks();
}

void Entity::displayActiveEffects() const {
    if (active_effects.empty()) {
        cout << "  (tidak ada efek aktif)\n";
        return;
    }
    for (const auto& effect : active_effects) {
        cout << "  - " << effect.name << " (" << effect.remaining_turns << " turn)\n";
    }
}

void Entity::applyPreyMark(const StatusPreyMark& prey_mark) {
    if (!active_prey_mark) {
        // First time: apply with initial stacks
        active_prey_mark = new StatusPreyMark(prey_mark);
        cout << "\n🎯 " << nama << " terkena Prey Mark! (" << active_prey_mark->stacks 
             << " stacks, -" << (active_prey_mark->stacks * 6) << "% DEF, durasi: " 
             << active_prey_mark->duration << " round)\n";
    } else {
        // Existing Prey: add stacks, refresh duration only for duration-bearing skills.
        int old_stacks = active_prey_mark->stacks;
        active_prey_mark->stacks = std::min(
            active_prey_mark->stacks + prey_mark.stacks,
            active_prey_mark->max_stacks);
        if (prey_mark.duration > 0) {
            active_prey_mark->duration = prey_mark.duration;
        }

        cout << "\n🎯 " << nama << " Prey Mark diperbarui! (" << old_stacks << " -> "
             << active_prey_mark->stacks << " stacks, -" << (active_prey_mark->stacks * 6)
             << "% DEF";
        if (prey_mark.duration > 0) {
            cout << ", durasi reset: " << active_prey_mark->duration << " round";
        }
        cout << ")\n";
    }
}

void Entity::removePreyMark(const string& mark_name) {
    if (active_prey_mark && active_prey_mark->name == mark_name) {
        cout << "\n🚫 " << nama << " Prey Mark dihilangkan.\n";
        delete active_prey_mark;
        active_prey_mark = nullptr;
    }
}

void Entity::updatePreyMarks() {
    if (active_prey_mark) {
        active_prey_mark->duration--;
        if (active_prey_mark->duration <= 0) {
            cout << "\n⏰ " << nama << " Prey Mark berakhir.\n";
            delete active_prey_mark;
            active_prey_mark = nullptr;
        }
    }
}

void Entity::displayActivePreyMarks() const {
    if (!active_prey_mark) {
        cout << "  (tidak ada Prey Mark)\n";
        return;
    }
    cout << "  - " << active_prey_mark->name << " (" << active_prey_mark->stacks 
         << "/" << active_prey_mark->max_stacks << " stacks, -" 
         << (active_prey_mark->stacks * 6) << "% DEF, " 
         << active_prey_mark->duration << " round)\n";
}

