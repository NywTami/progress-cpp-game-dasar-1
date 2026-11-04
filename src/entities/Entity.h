#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>
#include <vector>
#include "StatusEffect.h"

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
    map<string, int> resources;  // Flexible resource system: mana, faith, arrows, etc.
    vector<StatusEffect> active_effects;

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
    int getOriginalDefense() const { return defense; }
    int getOriginalAttackPower() const { return attack_power; }
    int getOriginalMaxHP() const { return max_hp; }

    void gainExp(int amount);
    void levelUp();

    // Status Effect system
    void applyEffect(const StatusEffect& effect);
    void removeEffect(const string& effect_name);
    void updateEffects();  // Reduce duration, remove expired effects
    void displayActiveEffects() const;
    const vector<StatusEffect>& getActiveEffects() const { return active_effects; }

    // Pure Virtual Function
    virtual void serang(Entity* target) = 0;
};

#endif
