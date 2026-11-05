#ifndef HUNTER_H
#define HUNTER_H

#include "Entity.h"

class Hunter : public Entity {
private:
    int energy;
    int max_energy;
    int focus;
    int max_focus;
    int pet_health;        // Companion pet HP

public:
    Hunter(string n, int h, int MaxHP, int atk, int def, int e, int max_e, int f, int max_f)
        : Entity(n, h, MaxHP, atk, def), energy(e), max_energy(max_e), focus(f), max_focus(max_f), pet_health(50) {}

    int getEnergy() const { return energy; }
    int getMaxEnergy() const { return max_energy; }
    int getFocus() const { return focus; }
    int getMaxFocus() const { return max_focus; }
    int getPetHealth() const { return pet_health; }

    void serang(Entity* target) override;
    void basicAttack(Entity* target);
    
    // Hunter Skills
    void powerShot(Entity* target);         // Cost: 20 energy, high damage single
    void beastCompanion(Entity* target);    // Cost: 25 energy, pet assists
    void trackingShot(Entity* target);      // Cost: 15 energy, debuff enemy
    void focusShot(Entity* target);        // Cost: 30 focus, high damage
    void disadvantageShot(Entity* target);   // Cost: 20 focus, reduces enemy defense
    void huntersMark(Entity* target);        // Cost: 25 focus, increases damage taken by enemy
    void regenEnergy(int amount);
    
};

#endif
