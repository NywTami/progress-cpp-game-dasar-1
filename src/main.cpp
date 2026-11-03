#include <iostream>
#include <cstdlib>
#include <ctime>
#include "entities/Support.h"
#include "entities/Knight.h"
#include "entities/Archer.h"
#include "entities/Monster.h"

using namespace std;

int main() {
    srand(time(0));

    string nama_support, nama_knight, nama_archer, nama_monster;

    cout << "===============================================================================================\n";
    cout << "==========               Selamat datang di Game Pertarungan Sederhana!               ==========\n";
    cout << "===============================================================================================\n";
    cout << endl;
    cout << "================================== Pembuatan Karakter =========================================\n";
    cout << "Masukkan nama Support: ";
    cin >> nama_support;

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

    //Support(nama, hp, max_hp, attack_power, defense, mana, max_mana);
    //Knight(nama, hp, max_hp, attack_power, defense, faith, max_faith);
    //Archer(nama, hp, max_hp, attack_power, defense ,arrows, max_arrows, mana, max_mana);
    //monster(nama,hp, max_hp, attack_power, defense)
    Support* p1 = new Support (nama_support, 100, 100, 20, 10, 50, 50);
    Knight* p2 = new Knight (nama_knight, 150, 150, 25, 15, 60, 60);
    Archer* p3 = new Archer (nama_archer, 80, 80, 180, 10, 10, 10, 60, 60);
    Monster* m1 = new Monster (nama_monster, 1200, 1200, 30, 12);

    cout << "=== BATTLE START: " << p1->getNama() << "|"<< p2->getNama() << "|" << p3->getNama() << " VS " << m1->getNama() << " ===\n";

    // Loop Pertarungan
    int turn = 1;
    while ((p1->isAlive() || p2->isAlive() || p3->isAlive()) && m1->isAlive()) {
        cout << "\n--- Turn " << turn << " ---\n";

        cout << "\nStatus:\n";
        cout << p1->getNama() << " - Level: " << p1->getLevel() << ", HP: " << p1->getHP() << "/" << p1->getMaxHP() << ", Mana: " << p1->getMana() << "/" << p1->getMaxMana() <<"\n";
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
            cout << "2. Heal (butuh 10 mana)\n";
            cout << "3. Mass Heal (butuh 25 mana)\n";
            cout << "4. Regen Mana\n";
            cout << "Pilihan: ";
            cin >> aksi;

            if (aksi == 1) {
                p1->serang(m1);
            } else if (aksi == 2) {
                int pilihan_target;
                cout << "\nPilih target untuk Heal:\n";
                cout << "1. " << p1->getNama() << "\n";
                cout << "2. " << p2->getNama() << "\n";
                cout << "3. " << p3->getNama() << "\n";
                cout << "Pilihan: ";
                cin >> pilihan_target;
                
                if (pilihan_target == 1) {
                    p1->heal(p1);
                } else if (pilihan_target == 2) {
                    p1->heal(p2);
                } else if (pilihan_target == 3) {
                    p1->heal(p3);
                }
            } else if (aksi == 3) {
                p1->massHeal(p1, p2, p3);
            } else if (aksi == 4) {
                p1->regenMana(15);
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
            cout << "6. Bless Defense (butuh 15 Faith)\n";
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
            } else if (aksi == 6) {
                int pilihan_target;
                cout << "\nPilih target untuk Bless Defense:\n";
                cout << "1. " << p1->getNama() << "\n";
                cout << "2. " << p2->getNama() << "\n";
                cout << "3. " << p3->getNama() << "\n";
                cout << "Pilihan: ";
                cin >> pilihan_target;
                
                if (pilihan_target == 1) {
                    p2->blessDefense(p1);
                } else if (pilihan_target == 2) {
                    p2->blessDefense(p2);
                } else if (pilihan_target == 3) {
                    p2->blessDefense(p3);
                }
            } else {
                cout << "Pilihan tidak valid. Giliran terlewat.\n";
            }
        } else if (pemain_pertama == p3) {
            cout << "\n" << p3->getNama() << " - Pilih aksi:\n";
            cout << "1. Serangan biasa\n";
            cout << "2. Basic Attack (tanpa panah)\n";
            cout << "3. Special Attack (butuh 20 mana dan 1 panah)\n";
            cout << "4. Reload Arrows\n";
            cout << "Pilihan: ";
            cin >> aksi;

            if (aksi == 1) {
                p3->serang(m1);
            } else if (aksi == 2) {
                p3->basicAttack(m1);
            } else if (aksi == 3) {
                p3->specialAttack(m1);
            } else if (aksi == 4) {
                p3->reloadArrows();
            } else {
                cout << "Pilihan tidak valid. Giliran terlewat.\n";
            }
        }

        if (!m1->isAlive()) {
            cout << "\nðŸŽ‰ " << m1->getNama() << " telah dikalahkan!\n";
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
                cout << "2. Heal (butuh 10 mana)\n";
                cout << "3. Mass Heal (butuh 25 mana)\n";
                cout << "4. Regen Mana\n";
                cout << "Pilihan: ";
                cin >> aksi;

                if (aksi == 1) {
                    p1->serang(m1);
                } else if (aksi == 2) {
                    int pilihan_target;
                    cout << "\nPilih target untuk Heal:\n";
                    cout << "1. " << p1->getNama() << "\n";
                    cout << "2. " << p2->getNama() << "\n";
                    cout << "3. " << p3->getNama() << "\n";
                    cout << "Pilihan: ";
                    cin >> pilihan_target;
                    
                    if (pilihan_target == 1) {
                        p1->heal(p1);
                    } else if (pilihan_target == 2) {
                        p1->heal(p2);
                    } else if (pilihan_target == 3) {
                        p1->heal(p3);
                    }
                } else if (aksi == 3) {
                    p1->massHeal(p1, p2, p3);
                } else if (aksi == 4) {
                    p1->regenMana(15);
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
                cout << "6. Bless Defense (butuh 15 Faith)\n";
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
                } else if (aksi == 6) {
                    int pilihan_target;
                    cout << "\nPilih target untuk Bless Defense:\n";
                    cout << "1. " << p1->getNama() << "\n";
                    cout << "2. " << p2->getNama() << "\n";
                    cout << "3. " << p3->getNama() << "\n";
                    cout << "Pilihan: ";
                    cin >> pilihan_target;

                    if (pilihan_target == 1) {
                        p2->blessDefense(p1);
                    } else if (pilihan_target == 2) {
                        p2->blessDefense(p2);
                    } else if (pilihan_target == 3) {
                        p2->blessDefense(p3);
                    }
                } else {
                    cout << "Pilihan tidak valid. Giliran terlewat.\n";
                }
            } else if (pemain_kedua == p3) {
                cout << "\n" << p3->getNama() << " - Pilih aksi:\n";
                cout << "1. Serangan biasa\n";
                cout << "2. Basic Attack (tanpa panah)\n";
                cout << "3. Special Attack (butuh 20 mana dan 1 panah)\n";
                cout << "4. Reload Arrows\n";
                cout << "Pilihan: ";
                cin >> aksi;

                if (aksi == 1) {
                    p3->serang(m1);
                } else if (aksi == 2) {
                    p3->basicAttack(m1);
                } else if (aksi == 3) {
                    p3->specialAttack(m1);
                } else if (aksi == 4) {
                    p3->reloadArrows();
                } else {
                    cout << "Pilihan tidak valid. Giliran terlewat.\n";
                }
            }
            
            if (!m1->isAlive()) {
                cout << "\nðŸŽ‰ " << m1->getNama() << " telah dikalahkan!\n";
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
            cout << "\nðŸŽ‰ " << m1->getNama() << " telah dikalahkan!\n";
            break;
        }

        // Cek apakah ada pemain yang mati
        if (!p1->isAlive()) {
            cout << "\nðŸ’€ " << p1->getNama() << " telah gugur dalam pertempuran...\n";
        }

        if (!p2->isAlive()) {
            cout << "\nðŸ’€ " << p2->getNama() << " telah gugur dalam pertempuran...\n";
        }

        if (!p3->isAlive()) {
            cout << "\nðŸ’€ " << p3->getNama() << " telah gugur dalam pertempuran...\n";
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
    cout << p1->getNama() << " - HP: " << p1->getHP() << "/" << p1->getMaxHP() << ", Mana: " << p1->getMana() << "/" << p1->getMaxMana() << "\n";
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
