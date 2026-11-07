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

    void serang(Entity* target) override; // Basic attack that consumes arrows = 1 //1
    void basicAttack(Entity* target); // Basic attack that not consumes arrows  //2
    void specialAttack(Entity* target); // Special attack that consumes both arrows = 1 and mana = 10/ /3
    void ultimateArrow(Entity* target); // Ultimate attack that consumes both arrows = 1 and mana = 25 //4
    void fireArrow(Entity* target); // Fire arrow attack that consumes mana = 10 //5
    void lightningArrow(Entity* target); // Lightning arrow attack that consumes mana = 15 //6
    void poisonArrow(Entity* target); // Poison arrow attack that consumes mana = 10 //7
    void multiShot(Entity* target); // Multi-shot attack that consumes both arrows = 2, mana = 15 //8
    void rapidFire(Entity* target); // Rapid fire attack that consumes mana = 30  //9
    void regenMana(); // Regenerate mana  //10
    void reloadArrows(); // Reload arrows to 40% of max_arrows //11
};

#endif
