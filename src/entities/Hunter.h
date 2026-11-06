#ifndef HUNTER_H
#define HUNTER_H

#include "Entity.h"

class Hunter : public Entity {
private:
    int energy;
    int max_energy;
    int pet_health;        // Companion pet HP

public:
    Hunter(string n, int h, int MaxHP, int atk, int def, int e, int max_e)
        : Entity(n, h, MaxHP, atk, def), energy(e), max_energy(max_e), pet_health(50) {}

    int getEnergy() const { return energy; }
    int getMaxEnergy() const { return max_energy; }
    int getPetHealth() const { return pet_health; }

    void serang(Entity* target) override;
    void basicAttack(Entity* target);
    
    // Hunter Skills
    void powerShot(Entity* target);         // Cost: 20 energy, high damage single
    void beastCompanion(Entity* target);    // Cost: 25 energy, pet assists, +1 Prey stack
    void trackingShot(Entity* target);      // Cost: 15 energy, pure damage
    void disadvantageShot(Entity* target);  // Cost: 20 energy, +2 Prey stacks if active
    void huntersMark(Entity* target);       // Cost: 10 energy, apply/refresh Prey
    void regenEnergy(int amount);
    
};

#endif
