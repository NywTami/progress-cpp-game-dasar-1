#include <iostream>
#include <string> // Dibutuhkan jika menggunakan tipe data string
using namespace std;

int main() {
    int angka_rahasia = 0;
    cout << "Selamat datang di permainan tebak angka!" << endl;
    cout << "Tebak angka antara 1-10: " << endl;
    while ( angka_rahasia != 7 ) {
        cout << "Tebak Angka: ";
        cin >> angka_rahasia;

        if ( angka_rahasia == 7 ) {
            cout << "Selamat, tebakanmu benar!" << endl;
        } else if ( angka_rahasia < 7 ) {
            cout << "Tebakanmu terlalu kecil, coba lagi!" << endl;
        } else {
            cout << "Tebakanmu terlalu besar, coba lagi!" << endl;
        }
    }
    return 0;
}