#ifndef KNIGHT_H
#define KNIGHT_H

#include "Entity.h"

class Knight : public Entity {
private:
    int faith;
    int max_faith;

public:
    int getFaith() const { return faith; }
    int getMaxfaith() const { return max_faith; }
    
    Knight(string n, int h, int MaxHP, int atk, int def, int f, int max_faith) 
        : Entity(n, h, MaxHP, atk, def), faith(f), max_faith(max_faith) {}

    void serang(Entity* target) override;
    void regenFaith(); //1
    void shieldBlock(); //2
    void powerStrike(Entity* target); //3
    void ultimateCharge(Entity* target); //4
    void blessDefense(Entity* target); //5
};

#endif
