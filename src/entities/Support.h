#ifndef SUPPORT_H
#define SUPPORT_H

#include "Entity.h"

class Support : public Entity {
private:
    int mana;
    int max_mana;

public:
    Support(string n, int h, int MaxHP, int atk, int def, int m, int MaxMana)
        : Entity(n, h, MaxHP, atk, def), mana(m), max_mana(MaxMana) {}

    int getMana() const override { return mana; }
    int getMaxMana() const { return max_mana; }

    void serang(Entity* target) override;
    void basicAttack(Entity* target);
    void heal(Entity* target);
    void massHeal(Entity* p1, Entity* p2, Entity* p3);
    void buffDefense(Entity* target);
    void buffAttackPower(Entity* target);
    void regenMana(int amount);
};

#endif
