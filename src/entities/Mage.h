#ifndef MAGE_H
#define MAGE_H

#include "Entity.h"

class Mage : public Entity {
private:
    int mana;
    int max_mana;

public:
    int getMana() const override { return mana; }
    int getMaxmana() const { return max_mana; }
    
    Mage(string n, int h, int MaxHP, int atk, int def, int m, int max_mana) 
        : Entity(n, h, MaxHP, atk, def), mana(m), max_mana(max_mana) {}

    void serang(Entity* target) override;
    void basicAttack(Entity* target);
    void fireball(Entity* target);
    void ultimateBurst(Entity* target);
    void regenMana(int amount);
};

#endif
