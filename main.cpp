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
    int defense;

public:
    Entity(string n, int h, int atk, int def) 
        : nama(n), hp(h), max_hp(h), attack_power(atk), defense(def) {}

    virtual ~Entity() {}

    // Getter
    string getNama() const { return nama; }
    int getHP() const { return hp; }
    int getDefense() const { return defense; }
    virtual int getMana() const { return 0; } 
    bool isAlive() const { return hp > 0; }

    // Metode menerima damage
    void terimaDamage(int damage) {
        double persen_reduksi = defense / 10.0;

        if (persen_reduksi > 100.0) {
            persen_reduksi = 100.0;
        } else if (persen_reduksi < 0.0) {
            persen_reduksi = 0.0;
        }

        int actual_damage = damage * (100.0 - persen_reduksi) / 100.0;

        hp -= actual_damage;

        if (hp < 0) {
            hp = 0;
        }

        cout << nama << " menerima " << actual_damage
             << " damage! (Defense: " << persen_reduksi
             << "%, Sisa HP: " << hp << "/" << max_hp << ")\n";
    }

    // Pure Virtual Function: Wajib ada agar child class bisa meng-override
    virtual void serang(Entity* target) = 0;
};

// 2. KELAS PEMAIN (PLAYER)
class Mage : public Entity {
private:
    int mana;

public:
    int getMana() const override { return mana; }
    Mage(string n, int h, int atk, int def, int m) 
        : Entity(n, h, atk, def), mana(m) {}

    void serang(Entity* target) override {
        cout << "\n⚔️ " << nama << " menyerang " << target->getNama() << " dengan Staff!\n";
        target->terimaDamage(attack_power);
    }

    // Metode untuk melakukan serangan dasar
    void basicAttack(Entity* target) {
        cout << "\n⚔️ " << nama << " menyerang " << target->getNama() << " dengan Pedang!\n";
        target->terimaDamage(attack_power);
    }

    // skill fireball
    void fireball(Entity* target) {
        if (mana >= 10) {
            mana -= 10;
            int damage_skill = attack_power + 15;
            cout << "\n🔥 " << nama << " menggunakan Skill Kritis [Fireball]! (Sisa Mana: " << mana << ")\n";
            target->terimaDamage(damage_skill);
        } else {
            cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk menggunakan Fireball! (Sisa Mana: " << mana << ")\n";
            basicAttack(target);
        }
    }
    // Skill Ultimate Burst
    void ultimateBurst(Entity* target) {
        if (mana >= 20) {
            mana -= 20;
            int damage_skill = attack_power * 2;
            cout << "\n🔥 " << nama << " menggunakan Skill Kritis [Ultimate Burst]! (Sisa Mana: " << mana << ")\n";
            target->terimaDamage(damage_skill);
        } else {
            cout << "\n⚠️ " << nama << " tidak memiliki cukup mana untuk menggunakan Ultimate Burst! (Sisa Mana: " << mana << ")\n";
            basicAttack(target);
        }
    }

};

class Knight : public Entity {
public:
    Knight(string n, int h, int atk, int def) 
        : Entity(n, h, atk, def) {}

    void serang(Entity* target) override {
        cout << "\n🛡️ " << nama << " menyerang " << target->getNama() << " dengan Pedang!\n";
        target->terimaDamage(attack_power);
    }

    void shieldBlock() {
        cout << "\n🛡️ " << nama << " menggunakan Shield Block untuk meningkatkan pertahanan!\n";
        defense += 10;
    }

    void powerStrike(Entity* target) {
        cout << "\n⚔️ " << nama << " menggunakan Power Strike!\n";
        int damage = attack_power + 20;
        target->terimaDamage(damage);
    }

    void ultimateCharge(Entity* target) {
        cout << "\n⚡ " << nama << " menggunakan Ultimate Charge!\n";
        int damage = attack_power * 2;
        target->terimaDamage(damage);
    }
};

// 3. KELAS MUSUH (MONSTER)
class Monster : public Entity {
public:
    Monster(string n, int h, int atk, int def) 
        : Entity(n, h, atk, def) {}

    void serang(Entity* target) override {
        cout << "\n🐾 " << nama << " menerjang " << target->getNama() << "!\n";
        target->terimaDamage(attack_power);
    }
};

// 4. MAIN LOOP PERTARUNGAN SEDERHANA
int main() {
    srand(time(0));

    string nama_mage, nama_knight, nama_monster;
    int hp_mage, atk_mage, def_mage, mana_mage;
    int hp_knight, atk_knight, def_knight;
    int hp_monster, atk_monster, def_monster;

    cout << "===============================================================================================\n";
    cout << "==========               Selamat datang di Game Pertarungan Sederhana!               ==========\n";
    cout << "===============================================================================================\n";
    cout << endl;
    cout << "================================== Pembuatan Karakter =========================================\n";
    cout << "Masukkan nama Mage: ";                           
    cin >> nama_mage;
    cout << "Masukkan HP Mage: ";
    cin >> hp_mage;
    cout << "Masukkan Attack Mage: ";
    cin >> atk_mage;
    cout << "Masukkan Defense Mage: ";
    cin >> def_mage;
    cout << "Masukkan Mana Mage: ";
    cin >> mana_mage;

    cout << "===============================================================================================\n";

    cout << "Masukkan nama Knight: ";
    cin >> nama_knight;
    cout << "Masukkan HP Knight: ";
    cin >> hp_knight;
    cout << "Masukkan Attack Knight: ";
    cin >> atk_knight;
    cout << "Masukkan Defense Knight: ";
    cin >> def_knight;

    cout << "===============================================================================================\n";

    cout << "Masukkan nama Monster: ";
    cin >> nama_monster;
    cout << "Masukkan HP Monster: ";
    cin >> hp_monster;
    cout << "Masukkan Attack Monster: ";
    cin >> atk_monster;
    cout << "Masukkan Defense Monster: ";
    cin >> def_monster;

    cout << "===============================================================================================\n";

    Mage* p1 = new Mage(nama_mage, hp_mage, atk_mage, def_mage, mana_mage);
    Knight* p2 = new Knight(nama_knight, hp_knight, atk_knight, def_knight);
    Monster* m1 = new Monster(nama_monster, hp_monster, atk_monster, def_monster);

    cout << "=== BATTLE START: " << p1->getNama() << " VS " << m1->getNama() << " ===\n";

    // Loop Pertarungan
    int turn = 1;
    while ((p1->isAlive() || p2->isAlive()) && m1->isAlive()) {
        cout << "\n--- Turn " << turn << " ---\n";

        cout << "\nStatus:\n";
        cout << p1->getNama() << " - HP: " << p1->getHP() << ", Mana: " << p1->getMana() << "\n";
        cout << p2->getNama() << " - HP: " << p2->getHP() << "\n";
        cout << m1->getNama() << " - HP: " << m1->getHP() << "\n";
        
        // Giliran Player
        int pilihan_pemain;
        cout << "\nPilih Hero:\n";
        cout << "1. " << p1->getNama() << "\n";
        cout << "2. " << p2->getNama() << "\n";
        cout << "Pilihan: ";
        cin >> pilihan_pemain;

        if (pilihan_pemain == 1 && !p1->isAlive()) {
            cout << p1->getNama() << " sudah gugur. Pilih hero lain.\n";
            continue;
        }

        if (pilihan_pemain == 2 && !p2->isAlive()) {
            cout << p2->getNama() << " sudah gugur. Pilih hero lain.\n";
            continue;
        }

        Entity* pemain_pertama = nullptr;
        Entity* pemain_kedua = nullptr;

        if (pilihan_pemain == 1) {
            pemain_pertama = p1;
            pemain_kedua = p2;
        } else if (pilihan_pemain == 2) {
            pemain_pertama = p2;
            pemain_kedua = p1;
        } else {
            cout << "Pilihan hero tidak valid.\n";
            continue;
        }

        int aksi;
        if (pemain_pertama == p1) {
            cout << "\n" << p1->getNama() << " - Pilih aksi:\n";
            cout << "1. Serangan biasa\n";
            cout << "2. fireball (butuh 10 mana)\n";
            cout << "3. Ultimate Burst (butuh 20 mana)\n";
            cout << "Pilihan: ";
            cin >> aksi;

            if (aksi == 1) {
                p1->serang(m1);
            } else if (aksi == 2) {
                p1->fireball(m1);
            } else if (aksi == 3) {
                p1->ultimateBurst(m1);
            } else {
                cout << "Pilihan tidak valid. Giliran terlewat.\n";
            }
        } else {
            cout << "\n" << p2->getNama() << " - Pilih aksi:\n";
            cout << "1. Serangan biasa\n";
            cout << "2. powerStrike\n";
            cout << "3. ultimateCharge\n";
            cout << "4. Shield Block (meningkatkan pertahanan)\n";
            cout << "Pilihan: ";
            cin >> aksi;

            if (aksi == 1) {
                p2->serang(m1);
            } else if (aksi == 2) {
                p2->powerStrike(m1);
            } else if (aksi == 3) {
                p2->ultimateCharge(m1);
            } else if (aksi == 4) {
                p2->shieldBlock();
            } else {
                cout << "Pilihan tidak valid. Giliran terlewat.\n";
            }
        }

        if (!m1->isAlive()) {
            cout << "\n🎉 " << m1->getNama() << " telah dikalahkan!\n";
            break;
        }
//      
        if (!pemain_kedua->isAlive()) {
            cout << pemain_kedua->getNama() << " sudah gugur dan melewati giliran.\n";
        } else {
            if (pemain_kedua == p1) {
                cout << "\n" << p1->getNama() << " - Pilih aksi:\n";
                cout << "1. Serangan biasa\n";
                cout << "2. fireball (butuh 10 mana)\n";
                cout << "3. Ultimate Burst (butuh 20 mana)\n";
                cout << "Pilihan: ";
                cin >> aksi;

                if (aksi == 1) {
                    p1->serang(m1);
                } else if (aksi == 2) {
                    p1->fireball(m1);
                } else if (aksi == 3) {
                    p1->ultimateBurst(m1);
                } else {
                    cout << "Pilihan tidak valid. Giliran terlewat.\n";
                }
            } else {
                cout << "\n" << p2->getNama() << " - Pilih aksi:\n";
                cout << "1. Serangan biasa\n";
                cout << "2. powerStrike\n";
                cout << "3. ultimateCharge\n";
                cout << "4. Shield Block (meningkatkan pertahanan)\n";
                cout << "Pilihan: ";
                cin >> aksi;

                if (aksi == 1) {
                    p2->serang(m1);
                } else if (aksi == 2) {
                    p2->powerStrike(m1);
                } else if (aksi == 3) {
                    p2->ultimateCharge(m1);
                } else if (aksi == 4) {
                    p2->shieldBlock();
                } else {
                    cout << "Pilihan tidak valid. Giliran terlewat.\n";
                }
            }
            
            if (!m1->isAlive()) {
                cout << "\n🎉 " << m1->getNama() << " telah dikalahkan!\n";
                break;
            } 
        }
        
        // Monster selalu menyerang sekali setiap turn
        if (p1->isAlive() && p2->isAlive()) {
            // Kedua pemain hidup, serang yang HP lebih rendah
            if (p1->getHP() <= p2->getHP()) {
                m1->serang(p1);
            } else {
                m1->serang(p2);
            }
        } else if (p1->isAlive()) {
            // Hanya p1 hidup
            m1->serang(p1);
        } else if (p2->isAlive()) {
            // Hanya p2 hidup
            m1->serang(p2);
        }
        
        if (!m1->isAlive()) {
            cout << "\n🎉 " << m1->getNama() << " telah dikalahkan!\n";
            break;
        }

        // Cek apakah ada pemain yang mati
        if (!p1->isAlive()) {
            cout << "\n💀 " << p1->getNama() << " telah gugur dalam pertempuran...\n";
        }

        if (!p2->isAlive()) {
            cout << "\n💀 " << p2->getNama() << " telah gugur dalam pertempuran...\n";
        }
        turn++;
    }
    cout << "\n=== BATTLE END ===\n";
    cout << "Hasil Pertarungan:\n";
    if (m1->isAlive()) {
        cout << "Monster " << m1->getNama() << " menang!\n";
    } else {
        cout << "Pemain menang!\n";
    }
    cout << "=============================\n";
    cout << "Status Akhir:\n";
    cout << p1->getNama() << " - HP: " << p1->getHP() << ", Mana: " << p1->getMana() << "\n";
    cout << p2->getNama() << " - HP: " << p2->getHP() << ", Mana: " << p2->getMana() << "\n";
    cout << m1->getNama() << " - HP: " << m1->getHP() << "\n";
    cout << "total turn: " << turn - 1 << "\n";
    cout << "Total damage diterima oleh " << p1->getNama() << ": " << (hp_mage - p1->getHP()) << "\n";
    cout << "Total damage diterima oleh " << p2->getNama() << ": " << (hp_knight - p2->getHP()) << "\n";
    cout << "Total damage diterima oleh " << m1->getNama() << ": " << (hp_monster - m1->getHP()) << "\n";   
    cout << "=============================\n";
    cout << "Terima kasih telah bermain!\n";
    cout << "=============================\n";
    

    // Pembersihan memori
    delete p1;
    delete m1;
    delete p2;

    return 0;
}