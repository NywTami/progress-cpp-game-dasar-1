#ifndef ARCHER_H
#define ARCHER_H

#include "Entity.h"

class Archer : public Entity {
private:
    int arrows;
    int max_arrows;
    int mana;
    int max_mana;

public:
    int getMana() const override { return mana; }
    int getMaxmana() const { return max_mana; }
    int getArrows() const { return arrows; }
    int getMaxarrows() const { return max_arrows; }
    
    Archer(string n, int h, int MaxHP, int atk, int def, int a, int max_arrows, int m, int max_mana)
        : Entity(n, h, MaxHP, atk, def), arrows(a), max_arrows(max_arrows), mana(m), max_mana(max_mana) {}

    void serang(Entity* target) override;
    void basicAttack(Entity* target);
    void specialAttack(Entity* target);
    void ultimateArrow(Entity* target);
    void fireArrow(Entity* target);
    void lightningArrow(Entity* target);
    void poisonArrow(Entity* target);
    void multiShot(Entity* target);
    void rapidFire(Entity* target);
    void regenMana();
    void reloadArrows();
};

#endif
