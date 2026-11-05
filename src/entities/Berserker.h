#ifndef BERSERKER_H
#define BERSERKER_H

#include "Entity.h"

class Berserker : public Entity {
private:
    int rage;
    int max_rage;
    int berserk_turns_remaining;   // 0 = normal, 1-4 = berserk aktif

    float calculateDamageMultiplier() const;
    void gainRage(int amount);

public:
    Berserker(string n, int h, int MaxHP, int atk)
        : Entity(n, h, MaxHP, atk, 0), rage(0), max_rage(300),
          berserk_turns_remaining(0) {}

    int getRage() const { return rage; }
    int getMaxRage() const { return max_rage; }
    int getBerserkTurns() const { return berserk_turns_remaining; }
    bool isBerserk() const { return berserk_turns_remaining > 0; }

    // Override terimaDamage untuk gain rage saat diserang
    void terimaDamage(int damage) override;

    void serang(Entity* target) override;

    // Skills — tanpa rage cost, pakai self-damage + rage gain
    void basicAttack(Entity* target);       // self-damage: 0%, rage gain: +20
    void rageStrike(Entity* target);        // self-damage: 5% maxHP, rage gain: +25
    void whirlwind(Entity* target);         // self-damage: 4% maxHP, rage gain: +20
    void selfHeal();                        // rage cost - 30, hp + 10%

    // Dipanggil di awal/akhir turn Berserker
    void updateBerserkMode();

    void displayStatus() const;
};

#endif
