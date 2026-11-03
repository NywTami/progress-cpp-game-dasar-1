#include <iostream>
#include <string>
using namespace std;

// 1. STRUCT
struct Reverse {
    string nama_faksi;
    int kapasitas;
};

// 2. KELAS INDUK (Abstract Base Class)
class Arcanist {
private:
    string nama;
    string afflatus;
    int bintang;

public:
    Arcanist(string n, string a, int b) {
        nama = n;
        afflatus = a;
        setbintang(b);
    }
    
    virtual ~Arcanist() {
        cout << "[Data Memori] Arcanist (" << nama << ") berhasil dihapus dari memori.\n";
    }
    
    void setbintang(int b) {
        if (b > 0 && b <= 6) {
            bintang = b;
        } else {
            bintang = 1;
        }
    }
    
    string getnama() const { return nama; }
    string getafflatus() const { return afflatus; }
    int getbintang() const { return bintang; }

    // DITAMBAHKAN: Pure Virtual Function untuk Polimorfisme
    virtual void cetakInfo() const = 0;
};

// 3. KELAS ANAK 1: Melania
class Melania : public Arcanist {
private:
    string senjata;
public:
    Melania(string n, string a, int b, string senjata1)
        : Arcanist(n, a, b), senjata(senjata1) {}
    
    void cetakInfo() const override {
        cout << "[Arcanist Melania] Nama: " << getnama()
             << " | Afflatus: " << getafflatus()
             << " | Bintang: " << getbintang() << "*"
             << " | Senjata: " << senjata << endl;
    }
};

// 4. KELAS ANAK 2: Vila
class Vila : public Arcanist {
private:
    string psycubs; 
public:
    Vila(string n, string a, int b, string psycubs1)
        : Arcanist(n, a, b), psycubs(psycubs1) {}
    
    void cetakInfo() const override {
        cout << "[Arcanist Vila]    Nama: " << getnama()
             << " | Afflatus: " << getafflatus()
             << " | Bintang: " << getbintang() << "*"
             << " | Psycubes: " << psycubs << endl;
    }
};

// 5. KELAS MANAJER ARCANIST
class ArcanistManager {
private:
    Reverse lokasi;                // Menggunakan struct Reverse
    Arcanist** daftar_arcanists;   // Array pointer dinamis
    int jumlah_arcanists;          // Jumlah karakter saat ini

public:
    ArcanistManager(string faksi, int kap) {
        lokasi.nama_faksi = faksi;
        lokasi.kapasitas = kap;
        jumlah_arcanists = 0;

        daftar_arcanists = new Arcanist*[lokasi.kapasitas];
    }

    ~ArcanistManager() {
        cout << "\n--- Persiapan untuk menghapus semua data Arcanist ---\n";
        for (int i = 0; i < jumlah_arcanists; ++i) {
            delete daftar_arcanists[i];
        }
        delete[] daftar_arcanists;
        daftar_arcanists = nullptr;
        cout << "[Data Memori] Semua data Arcanist berhasil dibebaskan dari Heap.\n";
    }

    void tambahArcanist(Arcanist* arcanist) {
        if (jumlah_arcanists < lokasi.kapasitas) {
            daftar_arcanists[jumlah_arcanists] = arcanist;
            jumlah_arcanists++;
            cout << "Berhasil menambahkan Arcanist: " << arcanist->getnama() << endl;
        } else {
            cout << "Kapasitas penuh! Tidak dapat menambahkan " << arcanist->getnama() << endl;
            delete arcanist; // Mencegah Memory Leak
        }
    }

    void cetakSemuaArcanist() const {
        cout << "\n=========================================================\n";
        cout << "Daftar Arcanist di Faksi (" << lokasi.nama_faksi << ") - Terisi: " 
             << jumlah_arcanists << "/" << lokasi.kapasitas << "\n";
        cout << "=========================================================\n";

        for (int i = 0; i < jumlah_arcanists; ++i) {
            daftar_arcanists[i]->cetakInfo();
        }
        cout << "=========================================================\n";
    }
};

// 6. MAIN FUNCTION
int main() {
    ArcanistManager manager("Foundation", 5);

    manager.tambahArcanist(new Melania("Melania Original", "Beast", 6, "Clockwork Mouse"));
    manager.tambahArcanist(new Vila("Vila Rusalka", "Plant", 6, "Song of Rusalka"));
    manager.tambahArcanist(new Melania("Melania Alt", "Beast", 5, "Steal Glove"));
    manager.tambahArcanist(new Vila("Vila Support", "Plant", 5, "Rusalka Wand"));
    manager.tambahArcanist(new Melania("Melania Scout", "Star", 4, "Dagger"));
    
    // Objek ini akan ditolak dan dihapus otomatis karena kapasitas garasi 5 (penuh)
    manager.tambahArcanist(new Vila("Vila Extra", "Mineral", 5, "Extra Book")); 

    manager.cetakSemuaArcanist();

    return 0;
}