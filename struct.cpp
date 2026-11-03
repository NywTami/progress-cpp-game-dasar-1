#include <iostream>
using namespace std;

struct buah {
    string nama;
    string rasa;
    string warna;
    double harga;
    float berat;
    
    void tampilkan() {
        cout << "Buah: " << nama << " | Rasa: " << rasa << " | Warna: " << warna <<" | Harga: Rp" << harga << " | Berat: "<< berat << " gr" << endl;
    }
};

struct mahasiswa {
    string nama;
    string npm;
    string gender;
    
    void tampilkan() {
        cout << "Nama: " << nama << " | NPM: " << npm << " | Gender: " << gender << endl;
    }
};

int main() {
    buah jeruk = {"Jeruk", "Manis", "Oren", 1500, 0.15};
    buah pisang = {"Pisang", "Manis", "Kuning", 2000, 0.40};
    buah apel = {"Apel", "Manis", "Merah", 4000, 0.60};
    buah anggur = {"Anggur", "Masam", "Ungu", 5000, 0.10};
    mahasiswa satu = {"Reza", "052", "Pria"};
    mahasiswa dua = {"Aman", "010", "Wanita"};
    
    jeruk.tampilkan();
    pisang.tampilkan();
    apel.tampilkan();
    anggur.tampilkan();
    
    satu.tampilkan();
    dua.tampilkan();
    
    // cout << "Buah: " << jeruk.nama << " | Rasa: " << jeruk.rasa << " | Warna: " << jeruk.warna <<" | Harga: Rp" << jeruk.harga << " | Berat: "<< jeruk.berat << " gr" << endl;
    // cout << "Buah: " << pisang.nama << " | Rasa: " << pisang.rasa << " | Warna: " << pisang.warna <<" | Harga: Rp" << pisang.harga << " | Berat: "<< pisang.berat << " gr" << endl;
    // cout << "Buah: " << apel.nama << " | Rasa: " << apel.rasa << " | Warna: " << apel.warna <<" | Harga: Rp" << apel.harga << " | Berat: "<< apel.berat << " gr" << endl;
    // cout << "Buah: " << anggur.nama << " | Rasa: " << anggur.rasa << " | Warna: " << anggur.warna <<" | Harga: Rp" << anggur.harga << " | Berat: "<< anggur.berat << " gr" << endl; 
    
    return 0;
}
