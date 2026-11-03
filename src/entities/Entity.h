#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

class Entity {
protected:
    string nama;
    int hp;
    int max_hp;
    int attack_power;
    int defense;
    int level;
    int exp;
    int max_exp;

public:
    Entity(string n, int h, int MaxHP, int atk, int def) 
        : nama(n), hp(h), max_hp(MaxHP), attack_power(atk), defense(def), level(1), exp(0), max_exp(100) {}

    virtual ~Entity() {}

    // Getter
    string getNama() const { return nama; }
    int getHP() const { return hp; }
    int getMaxHP() const { return max_hp; }
    int getDefense() const { return defense; }
    int getLevel() const { return level; }
    int getExp() const { return exp; }
    int getMaxExp() const { return max_exp; }
    virtual int getMana() const { return 0; }
    bool isAlive() const { return hp > 0; }

    // Metode menerima damage
    void terimaDamage(int damage);

    // Metode healing dan buff
    void pulihkanHP(int amount);
    void tambahDefense(int amount);
    void resetDefense(int original_defense);
    int getAttackPower() const { return attack_power; }

    void gainExp(int amount);

    void levelUp();

    // Pure Virtual Function
    virtual void serang(Entity* target) = 0;
};

#endif
