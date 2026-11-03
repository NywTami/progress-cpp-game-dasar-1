#include "Monster.h"
#include <iostream>

void Monster::serang(Entity* target) {
    cout << "\n🐾 " << nama << " menerjang " << target->getNama() << "!\n";
    target->terimaDamage(attack_power);
}
