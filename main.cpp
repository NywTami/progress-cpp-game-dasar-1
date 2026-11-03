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

    void gainExp(int amount) {
        exp += amount;
        cout << nama << " mendapat " << amount << " exp!\n";
        if (exp >= max_exp) {
            levelUp();
        }
    }

    void levelUp() {
        level++;
        exp = 0;
        max_exp = level * 100;
        attack_power += 5;
        defense += 3;
        hp += 20;
        max_hp = hp;
        cout << "\n⭐ " << nama << " naik level ke " << level << "!\n";
        cout << "Attack: +" << 5 << ", Defense: +" << 3 << ", HP: +" << 20 << "\n";
    }

    // Pure Virtual Function: Wajib ada agar child class bisa meng-override
    virtual void serang(Entity* target) = 0;
};

// 2. KELAS PEMAIN (PLAYER)
class Mage : public Entity {
private:
    int mana;
    int max_mana;

public:
    int getMana() const override { return mana; }
    int getMaxmana() const { return max_mana; }
    
    Mage(string n, int h, int MaxHP, int atk, int def, int m, int max_mana) 
        : Entity(n, h, MaxHP, atk, def), mana(m), max_mana(max_mana) {}

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
private:
    int faith;
    int max_faith;

public:
    int getFaith() const { return faith; }
    int getMaxfaith() const { return max_faith; }
    
    Knight(string n, int h, int MaxHP, int atk, int def, int f, int max_faith) 
        : Entity(n, h, MaxHP, atk, def), faith(f), max_faith(max_faith) {}

    void regenFaith() {
        faith += 20;
        cout << "\n🛡️ " << nama << "Menggunakan Regen Faith, Faith + 20 \n";
    }
    
    void serang(Entity* target) override {
        cout << "\n🛡️ " << nama << " menyerang " << target->getNama() << " dengan Pedang!\n";
        target->terimaDamage(attack_power);
    }
    
    void shieldBlock() {
        if (faith >= 20) {
            faith -= 20;
            cout << "\n🛡️ " << nama << " menggunakan Shield Block untuk meningkatkan pertahanan!\n";
            defense += 10;
        } else {
            cout << "Tidak Memiliki cukup Faith! (Faith : " << faith << ")\n";
            cout << "Mengcast Regen Faith\n";
            regenFaith();
        }
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

    void serang(Entity* target) override {
        if (arrows > 0) {
            arrows--;
            cout << "\n🏹 " << nama << " menembak " << target->getNama() << " dengan panah!\n";
            target->terimaDamage(attack_power);
        } else {
            cout << "\n🏹 " << nama << " kehabisan panah!\n";
            reloadArrows();
        }
    }

    void reloadArrows() {
        arrows = arrows + 1;
        cout << "\n🏹 " << nama << " mengisi ulang anak panah sebanyak 1!\n";
    }

    void specialAttack(Entity* target) {
        if (arrows > 0) {
            if (mana >= 20) {
                arrows --;
                mana -= 20;
                cout << "\n🏹 " << nama << " Menggunakan Special Attack !\n";
                int damage = attack_power * 1.5;
                target->terimaDamage(damage);
            } else {
                cout << "!!!!! " << nama << "Tidak Memiliki cukup mana " << mana << "/" << max_mana << " !!!!!" << endl;
                arrows --;
                target->terimaDamage(attack_power);
            }
        } else {
            cout << "\n🏹 " << nama << " kehabisan panah!\n";
            reloadArrows();
        }
    }
};

// 3. KELAS MUSUH (MONSTER)
class Monster : public Entity {
public:
    Monster(string n, int h, int Mh, int atk, int def) 
        : Entity(n, h, Mh, atk, def) {}

    void serang(Entity* target) override {
        cout << "\n🐾 " << nama << " menerjang " << target->getNama() << "!\n";
        target->terimaDamage(attack_power);
    }
};

// 4. MAIN LOOP PERTARUNGAN SEDERHANA
int main() {
    srand(time(0));

    string nama_mage, nama_knight, nama_archer, nama_monster;

    cout << "===============================================================================================\n";
    cout << "==========               Selamat datang di Game Pertarungan Sederhana!               ==========\n";
    cout << "===============================================================================================\n";
    cout << endl;
    cout << "================================== Pembuatan Karakter =========================================\n";
    cout << "Masukkan nama Mage: ";                           
    cin >> nama_mage;

    cout << "===============================================================================================\n";

    cout << "Masukkan nama Knight: ";
    cin >> nama_knight;

    cout << "===============================================================================================\n";
    
    cout << "Masukkan nama Archer: ";
    cin >> nama_archer;

    cout << "===============================================================================================\n";

    cout << "Masukkan nama Monster: ";
    cin >> nama_monster;

    cout << "===============================================================================================\n";

    //Mage(nama, hp, max_hp, attack_power, defense, mana, max_mana);
    //Knight(nama, hp, max_hp, attack_power, defense, faith, max_faith);
    //Archer(nama, hp, max_hp, attack_power, defense ,arrows, max_arrows, mana, max_mana);
    //monster(nama,hp, max_hp, attack_power, defense)
    Mage* p1 = new Mage (nama_mage, 100, 100, 20, 10, 50, 50);
    Knight* p2 = new Knight (nama_knight, 150, 150, 25, 15, 60, 60);
    Archer* p3 = new Archer (nama_archer, 80, 80, 180, 10, 10, 10, 60, 60);
    Monster* m1 = new Monster (nama_monster, 1200, 1200, 30, 12);

    cout << "=== BATTLE START: " << p1->getNama() << "|"<< p2->getNama() << "|" << p3->getNama() << " VS " << m1->getNama() << " ===\n";

    // Loop Pertarungan
    int turn = 1;
    while ((p1->isAlive() || p2->isAlive() || p3->isAlive()) && m1->isAlive()) {
        cout << "\n--- Turn " << turn << " ---\n";

        cout << "\nStatus:\n";
        cout << p1->getNama() << " - Level: " << p1->getLevel() << ", HP: " << p1->getHP() << "/" << p1->getMaxHP() << ", Mana: " << p1->getMana() << "/" << p1->getMaxmana() <<"\n";
        cout << p2->getNama() << " - Level: " << p2->getLevel() << ", HP: " << p2->getHP() << "/" << p2->getMaxHP() << ", Faith: " << p2->getFaith() << "/" << p2->getMaxfaith() <<"\n";
        cout << p3->getNama() << " - Level: " << p3->getLevel() << ", HP: " << p3->getHP() << "/" << p3->getMaxHP() << ", Arrows: "<< p3->getArrows() << "/" << p3->getMaxarrows() << ", Mana: " << p3->getMana() << "/" << p3->getMaxmana() <<"\n";
        cout << m1->getNama() << " - HP: " << m1->getHP() << "/" << m1->getMaxHP() << "\n";

        // Giliran Player
        int pilihan_pemain;
        cout << "\nPilih Hero:\n";
        cout << "1. " << p1->getNama() << "\n";
        cout << "2. " << p2->getNama() << "\n";
        cout << "3. " << p3->getNama() << "\n";
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
        if (pilihan_pemain == 3 && !p3->isAlive()) {
            cout << p3->getNama() << " sudah gugur. Pilih hero lain.\n";
            continue;
        }
        Entity* pemain_pertama = nullptr;
        Entity* pemain_kedua = nullptr;
        Entity* pemain_ketiga = nullptr;

        if (pilihan_pemain == 1) {
            pemain_pertama = p1;
            
            int pilihan_kedua;
            cout << "\nPilih Hero Kedua:\n";
            cout << "2. " << p2->getNama() << "\n";
            cout << "3. " << p3->getNama() << "\n";
            cout << "Pilihan: ";
            cin >> pilihan_kedua;

            if (pilihan_kedua == 2 && p2->isAlive()) {
                pemain_kedua = p2;
            } else if (pilihan_kedua == 3 && p3->isAlive()) {
                pemain_kedua = p3;
            } else {
                cout << "Pilihan hero tidak valid.\n";
                continue;
            }
        } else if (pilihan_pemain == 2) {
            pemain_pertama = p2;
            int pilihan_kedua;
            cout << "\nPilih Hero Kedua:\n";
            cout << "1. " << p1->getNama() << "\n";
            cout << "3. " << p3->getNama() << "\n";
            cout << "Pilihan: ";
            cin >> pilihan_kedua;

            if (pilihan_kedua == 1 && p1->isAlive()) {
                pemain_kedua = p1;
            } else if (pilihan_kedua == 3 && p3->isAlive()) {
                pemain_kedua = p3;
            } else {
                cout << "Pilihan hero tidak valid.\n";
                continue;
            }
        } else if (pilihan_pemain == 3) {
            pemain_pertama = p3;
            int pilihan_kedua;
            cout << "\nPilih Hero Kedua:\n";
            cout << "1. " << p1->getNama() << "\n";
            cout << "2. " << p2->getNama() << "\n";
            cout << "Pilihan: ";
            cin >> pilihan_kedua;

            if (pilihan_kedua == 1 && p1->isAlive()) {
                pemain_kedua = p1;
            } else if (pilihan_kedua == 2 && p2->isAlive()) {
                pemain_kedua = p2;
            } else {
                cout << "Pilihan hero tidak valid.\n";
                continue;
            }
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
        } else if (pemain_pertama == p2) {
            cout << "\n" << p2->getNama() << " - Pilih aksi:\n";
            cout << "1. Serangan biasa\n";
            cout << "2. powerStrike\n";
            cout << "3. ultimateCharge\n";
            cout << "4. Shield Block (butuh 20 Faith)\n";
            cout << "5. Regen Faith\n";
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
            } else if (aksi == 5) {
                p2->regenFaith();
            } else {
                cout << "Pilihan tidak valid. Giliran terlewat.\n";
            }
        } else if (pemain_pertama == p3) {
            cout << "\n" << p3->getNama() << " - Pilih aksi:\n";
            cout << "1. Serangan biasa\n";
            cout << "2. Special Attack (butuh 20 mana dan 1 panah)\n";
            cout << "3. Reload Arrows\n";
            cout << "Pilihan: ";
            cin >> aksi;

            if (aksi == 1) {
                p3->serang(m1);
            } else if (aksi == 2) {
                p3->specialAttack(m1);
            } else if (aksi == 3) {
                p3->reloadArrows();
            } else {
                cout << "Pilihan tidak valid. Giliran terlewat.\n";
            }
        }

        if (!m1->isAlive()) {
            cout << "\n🎉 " << m1->getNama() << " telah dikalahkan!\n";
            int exp_reward = 50;
            p1->gainExp(exp_reward);
            if (p2->isAlive()) p2->gainExp(exp_reward);
            if (p3->isAlive()) p3->gainExp(exp_reward);
            break;
        }
        
        if (!pemain_kedua->isAlive()) {
            cout << pemain_kedua->getNama() << " sudah gugur and melewati giliran.\n";
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
            } else if (pemain_kedua == p2) {
                cout << "\n" << p2->getNama() << " - Pilih aksi:\n";
                cout << "1. Serangan biasa\n";
                cout << "2. powerStrike\n";
                cout << "3. ultimateCharge\n";
                cout << "4. Shield Block (butuh 20 Faith)\n";
                cout << "5. Regen Faith\n";
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
                } else if (aksi == 5) {
                    p2->regenFaith();
                } else {
                    cout << "Pilihan tidak valid. Giliran terlewat.\n";
                }
            } else if (pemain_kedua == p3) {
                cout << "\n" << p3->getNama() << " - Pilih aksi:\n";
                cout << "1. Serangan biasa\n";
                cout << "2. Special Attack (butuh 20 mana dan 1 panah)\n";
                cout << "3. Reload Arrows\n";
                cout << "Pilihan: ";
                cin >> aksi;

                if (aksi == 1) {
                    p3->serang(m1);
                } else if (aksi == 2) {
                    p3->specialAttack(m1);
                } else if (aksi == 3) {
                    p3->reloadArrows();
                } else {
                    cout << "Pilihan tidak valid. Giliran terlewat.\n";
                }
            }
            
            if (!m1->isAlive()) {
                cout << "\n🎉 " << m1->getNama() << " telah dikalahkan!\n";
                int exp_reward = 50;
                p1->gainExp(exp_reward);
                if (p2->isAlive()) p2->gainExp(exp_reward);
                if (p3->isAlive()) p3->gainExp(exp_reward);
                break;
            } 
        }
        
        // Monster selalu menyerang sekali setiap turn
        if (p1->isAlive() && p2->isAlive() && p3->isAlive()) {
            int target_random = rand() % 3;
            if (target_random == 0) {
                m1->serang(p1);
            } else if (target_random == 1) {
                m1->serang(p2);
            } else {
                m1->serang(p3);
            }
        } else if (p1->isAlive() && p2->isAlive()) {
            int target_random = rand() % 2;
            if (target_random == 0) {
                m1->serang(p1);
            } else {
                m1->serang(p2);
            }
        } else if (p1->isAlive() && p3->isAlive()) {
            int target_random = rand() % 2;
            if (target_random == 0) {
                m1->serang(p1);
            } else {
                m1->serang(p3);
            }
        } else if (p2->isAlive() && p3->isAlive()) {
            int target_random = rand() % 2;
            if (target_random == 0) {
                m1->serang(p2);
            } else {
                m1->serang(p3);
            }
        } else if (p1->isAlive()) {
            m1->serang(p1);
        } else if (p2->isAlive()) {
            m1->serang(p2);
        } else if (p3->isAlive()) {
            m1->serang(p3);
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

        if (!p3->isAlive()) {
            cout << "\n💀 " << p3->getNama() << " telah gugur dalam pertempuran...\n";
        }
        cout << "===============================================================================================\n";
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
    cout << p1->getNama() << " - HP: " << p1->getHP() << "/" << p1->getMaxHP() << ", Mana: " << p1->getMana() << "/" << p1->getMaxmana() << "\n";
    cout << p2->getNama() << " - HP: " << p2->getHP() << "/" << p2->getMaxHP() << ", Faith: " << p2->getFaith() << "/" << p2->getMaxfaith() << "\n";
    cout << p3->getNama() << " - HP: " << p3->getHP() << "/" << p3->getMaxHP() << ", Arrows: " << p3->getArrows() << "/" << p3->getMaxarrows() << ", Mana: " << p3->getMana() << "/" << p3->getMaxmana() << "\n";
    cout << m1->getNama() << " - HP: " << m1->getHP() << "/" << m1->getMaxHP() << "\n";
    cout << "total turn: " << turn - 1 << "\n";
    cout << "Total damage diterima oleh " << p1->getNama() << ": " << (p1->getMaxHP() - p1->getHP()) << "\n";
    cout << "Total damage diterima oleh " << p2->getNama() << ": " << (p2->getMaxHP() - p2->getHP()) << "\n";
    cout << "Total damage diterima oleh " << p3->getNama() << ": " << (p3->getMaxHP() - p3->getHP()) << "\n";
    cout << "Total damage diterima oleh " << m1->getNama() << ": " << (m1->getMaxHP() - m1->getHP()) << "\n";   
    cout << "=============================\n";
    cout << "Terima kasih telah bermain!\n";
    cout << "=============================\n";
    

    // Pembersihan memori
    delete p1;
    delete p2;
    delete p3;
    delete m1;

    return 0;
}