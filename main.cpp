#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// 1. KELAS INDUK (ABSTRACT BASE CLASS)
class Entity {
protected:
    string nama;
    int hp;
    int max_hp;
    int attack_power;

public:
    Entity(string n, int h, int atk) 
        : nama(n), hp(h), max_hp(h), attack_power(atk) {}

    virtual ~Entity() {}

    // Getter
    string getNama() const { return nama; }
    int getHP() const { return hp; }
    bool isAlive() const { return hp > 0; }

    // Metode menerima damage
    void terimaDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
        cout << nama << " menerima " << damage << " damage! (Sisa HP: " << hp << "/" << max_hp << ")\n";
    }

    // Pure Virtual Function: Setiap karakter punya cara menyerang berbeda
    virtual void serang(Entity* target) = 0;
};

// 2. KELAS PEMAIN (PLAYER)
class Player : public Entity {
private:
    int mana;

public:
    Player(string n, int h, int atk, int m) 
        : Entity(n, h, atk), mana(m) {}

    void serang(Entity* target) override {
        cout << "\n⚔️ " << nama << " menyerang " << target->getNama() << " dengan Pedang!\n";
        target->terimaDamage(attack_power);
    }

    void skilKhusus(Entity* target) {
        if (mana >= 20) {
            mana -= 20;
            int damage_skill = attack_power * 2;
            cout << "\n🔥 " << nama << " menggunakan Skill Kritis [Ultimate Burst]! (Sisa Mana: " << mana << ")\n";
            target->terimaDamage(damage_skill);
        } else {
            cout << "\n❌ Mana tidak cukup! Menggunakan serangan biasa.\n";
            serang(target);
        }
    }
};

// 3. KELAS MUSUH (MONSTER)
class Monster : public Entity {
public:
    Monster(string n, int h, int atk) 
        : Entity(n, h, atk) {}

    void serang(Entity* target) override {
        cout << "\n🐾 " << nama << " menerjang " << target->getNama() << "!\n";
        target->terimaDamage(attack_power);
    }
};

// 4. MAIN LOOP PERTARUNGAN SEDERHANA
int main() {
    srand(time(0)); // Seed acak

    Player* p1 = new Player("Hero", 100, 15, 40);
    Monster* m1 = new Monster("Slime King", 80, 10);

    cout << "=== BATTLE START: " << p1->getNama() << " VS " << m1->getNama() << " ===\n";

    // Loop Pertarungan sederetan giliran
    int turn = 1;
    while (p1->isAlive() && m1->isAlive()) {
        cout << "\n--- Turn " << turn << " ---\n";
        
        // Giliran Player
        p1->skilKhusus(m1);

        // Cek apakah musuh kalah
        if (!m1->isAlive()) {
            cout << "\n🎉 " << m1->getNama() << " telah dikalahkan!\n";
            break;
        }

        // Giliran Musuh
        m1->serang(p1);

        // Cek apakah player kalah
        if (!p1->isAlive()) {
            cout << "\n💀 " << p1->getNama() << " telah gugur dalam pertempuran...\n";
            break;
        }

        turn++;
    }

    // Pembersihan memori
    delete p1;
    delete m1;

    return 0;
}