#ifndef SUMMONER_H
#define SUMMONER_H

#include "Entity.h"

class Summoner : public Entity {
private:
    int mana;
    int max_mana;
    int summon_count;      // Active summons

public:
    Summoner(string n, int h, int MaxHP, int atk, int def, int m, int max_m)
        : Entity(n, h, MaxHP, atk, def), mana(m), max_mana(max_m), summon_count(0) {}

    int getMana() const override { return mana; }
    int getMaxMana() const { return max_mana; }
    int getSummonCount() const { return summon_count; }

    void serang(Entity* target) override;
    void basicAttack(Entity* target);
    
    // Summoner Skills
    void summonAlly(Entity* target);        // Cost: 30 mana, summon pet to assist
    void arcaneBurst(Entity* target);       // Cost: 25 mana, magical AoE damage
    void manaShield();                      // Cost: 15 mana, temporary damage reduction
    void regenMana(int amount);
};

#endif
