#include <iostream>
#include <string>
#include <cstdlib>
#define MAX 10

using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    int jumlahNilai;
    int nilai[MAX];
    float rataRata;
    char nilaiHuruf;
};

Mahasiswa antrian[MAX];
int head = 0;
int tail = 0;

// Fungsi Hitung Rata-Rata
float rataRata(int* p, int n){
    float total = 0;

    for (int i = 0; i < n; i++){
        total += *(p + i);
    }

    return (n > 0) ? total / n : 0;
}

// Fungsi Tentukan Nilai Huruf
char tentukanNilaiHuruf(float rata){
    if (rata >= 85){
        return 'A';
    } else if (rata >= 70){
        return 'B';
    } else if (rata >= 60){
        return 'C';
    } else {
        return 'D';
    }
}

// === Fungsi Pengecekan Queue ===
bool isFull(){
    if (tail == MAX){
        return true;
    } else {
        return false;
    }
}

bool isEmpty(){
    if (tail == 0 && head == 0){
        return true;
    } else {
        return false;
    }
}

// === Fungsi Enqueue ===
void enqueue(){
    if (isFull()){
        cout << "\n==== Antrean Penuh ====" << endl;
        return;
    } else {
        // Jika Masih Ada Ruang
        cout << "\n==== Input Data ====" << endl;
        cout << "Masukkan Nama Mahasiswa : ";
        getline(cin, antrian[tail].nama);
        cout << "Masukkan NIM Mahasiswa : ";
        getline(cin, antrian[tail].nim);
        cout << "Masukkan Jumlah Nilai : ";
        cin >> antrian[tail].jumlahNilai;

        cout << "\n"; // Baris Kosong

        // Pointer Untuk Memasukkan & Mengakses Data Array Nilai
        int* p = antrian[tail].nilai;

        // Loop Untuk Input Nilai Sesuai Jumlah Nilai
        for (int i = 0; i < antrian[tail].jumlahNilai; i++){
            cout << "Masukkan Nilai ke-" << i + 1 << " = ";
            cin >> *(p + i);
        }
        cin.ignore(); // Bersihkan Buffer

        // Mencari Nilai Rata-Rata dan Nilai Huruf Menggunakan Fungsi Yang Sudah Ada
        antrian[tail].rataRata = rataRata(p, antrian[tail].jumlahNilai);
        antrian[tail].nilaiHuruf = tentukanNilaiHuruf(antrian[tail].rataRata);

        tail++;
        cout << "\n==== Data Berhasil Ditambahkan ====" << endl;
    }
}

// === Fungsi Dequeue ===
void dequeue(){
    if (isEmpty()){
        cout << "\n==== Antrean Kosong ====" << endl;
    } else {
        cout << "\n==== Data Mahasiswa Bernama -- " << antrian[head].nama << " -- Berhasil Dihapus ====" << endl;
        // Loop Untuk Menimpa Dan Memajukan Data
        for (int i = head; i < tail - 1; i++){
            antrian[i] = antrian[i + 1];
        }

        tail--; // Geser Ke Depan
    }
}

// === Fungsi Tampilkan ===
void tampilkan(){
    if (isEmpty()){
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    } else {
        cout << "\n==== Data Saat Ini ====" << endl;

        // Loop Untuk Menampilkan Data
        for (int i = head; i < tail; i++){
            cout << "Nama\t\t : " << antrian[i].nama << endl;
            cout << "NIM\t\t : " << antrian[i].nim << endl;
            
            cout << "\n"; // Baris Kosong

            int* p = antrian[i].nilai;

            // Loop Untuk Menampilkan Nilai
            for (int j = 0; j < antrian[i].jumlahNilai; j++){
                cout << "Nilai ke-" << j + 1 << "\t = " << *(p + j) << endl;
            }

            cout << "\nNilai Rata-Rata\t = " << antrian[i].rataRata << endl;
            cout << "Nilai Huruf\t = " << antrian[i].nilaiHuruf << endl;
            cout << "--------------------------\n";
        }
    }
}

// === Fungsi Bersihkan (Hapus Semua Data) ===
void bersihkan(){
    if (isEmpty()){
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    } else {
        tail = 0;
        head = 0;
        cout << "\n==== Seluruh Data Dibersihkan ====" << endl;
    }    
}

// === Fungsi Sorting Berdasarkan Rata-Rata (DESC) ===
void urutkanSelection(){
    if (tail <= 1){
        cout << "\n==== Belum Cukup Data Untuk Diurutkan ====" << endl;
    } else {
        for (int i = head; i < tail - 1; i++){
            int maxIndex = i;

            // Loop untuk mengurutkan dari yang terbesar ke yang terkecil (DESC)
            for (int j = i + 1; j < tail; j++){
                if (antrian[j].rataRata > antrian[maxIndex].rataRata){
                    maxIndex = j;
                }
            }

            if (maxIndex != i){
                Mahasiswa temp = antrian[i];
                antrian[i] = antrian[maxIndex];
                antrian[maxIndex] = temp;
            }
        }
        cout << "\n==== Data berhasil diurutkan berdasarkan Rata-Rata ====" << endl;
        tampilkan();
    }
}

// === Fungsi Sorting Berdasarkan Nama (ASC) ===
void urutkanByNama() {
    for (int i = 0; i < tail - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < tail; j++) {
            if (antrian[j].nama < antrian[minIndex].nama) {
                minIndex = j;
            }
        }
        Mahasiswa temp = antrian[i];
        antrian[i] = antrian[minIndex];
        antrian[minIndex] = temp;
    }
}

// === Fungsi Sorting Berdasarkan NIM (ASC) ===
void urutkanByNIM() {
    for (int i = 0; i < tail - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < tail; j++) {
            if (antrian[j].nim < antrian[minIndex].nim) {
                minIndex = j;
            }
        }
        Mahasiswa temp = antrian[i];
        antrian[i] = antrian[minIndex];
        antrian[minIndex] = temp;
    }
}

// === Fungsi Cari Berdasarkan Nama (Binary Search) ===
void cariByNama() {
    if (isEmpty()) {
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    }

    // Memanggil fungsi sorting sebelum binary search
    urutkanByNama();

    string cari;
    cout << "Masukkan Nama yang dicari: ";
    getline(cin, cari);

    int kiri = 0, kanan = tail - 1;
    bool found = false;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        if (antrian[tengah].nama == cari) {
            cout << "\n==== Data --" << cari << "-- Ditemukan (Hasil Binary Search) ====" << endl;
            cout << "Nama\t\t : " << antrian[tengah].nama << endl;
            cout << "NIM\t\t : " << antrian[tengah].nim << endl;
            cout << "Nilai Rata-Rata\t = " << antrian[tengah].rataRata << endl;
            cout << "Nilai Huruf\t = " << antrian[tengah].nilaiHuruf << endl;
            cout << "--------------------------" << endl;
            found = true;
            break;
        } else if (antrian[tengah].nama < cari) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }

    if (!found) {
        cout << "\n==== Data dengan Nama --" << cari << "-- Tidak Ditemukan ====" << endl;
    }
}

// === Fungsi Cari Berdasarkan NIM (Binary Search) ===
void cariByNIM() {
    if (isEmpty()) {
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    }

    // Panggil fungsi sorting sebelum binary search
    urutkanByNIM();

    string cari;
    cout << "Masukkan NIM yang dicari: ";
    getline(cin, cari);

    int kiri = 0, kanan = tail - 1;
    bool found = false;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        if (antrian[tengah].nim == cari) {
            cout << "\n==== Data --" << cari << "-- Ditemukan (Hasil Binary Search) ====" << endl;
            cout << "Nama\t\t : " << antrian[tengah].nama << endl;
            cout << "NIM\t\t : " << antrian[tengah].nim << endl;
            cout << "Nilai Rata-Rata\t = " << antrian[tengah].rataRata << endl;
            cout << "Nilai Huruf\t = " << antrian[tengah].nilaiHuruf << endl;
            cout << "--------------------------" << endl;
            found = true;
            break;
        } else if (antrian[tengah].nim < cari) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }

    if (!found) {
        cout << "\n==== Data dengan NIM --" << cari << "-- Tidak Ditemukan ====" << endl;
    }
}

int main(){
    int pilihan;
    do {
        cout << "\n==== MENU UTAMA ====" << endl;
        cout << "1. Input Data" << endl;
        cout << "2. Hapus Data" << endl;
        cout << "3. Tampilkan Data" << endl;
        cout << "4. Bersihkan Data" << endl;
        cout << "5. Urutkan Data (Selection Sort)" << endl;
        cout << "6. Cari Data" << endl;
        cout << "7. Keluar" << endl;

        cout << "Masukkan Pilihan (1-7) : ";
        cin >> pilihan;
        cin.ignore();

        // Switch Case
        switch (pilihan)
        {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            tampilkan();
            break;
        case 4:
            bersihkan();
            break;
        case 5:
            urutkanSelection();
            break;
        case 6:
            system("cls"); // Bersihkan Console                
        
            // Menu pilihan pencarian berdasarkan kategori
            int pilihanCari;
            do {
                cout << "\n==== MENU PENCARIAN ====" << endl;
                cout << "1. Cari Berdasarkan Nama" << endl;
                cout << "2. Cari Berdasarkan NIM" << endl;
                cout << "3. Keluar" << endl;

                cout << "Masukkan Pilihan (1-3) : ";
                cin >> pilihanCari;
                cin.ignore();

                switch (pilihanCari)
                {
                case 1:
                    cariByNama();
                    break;
                case 2:
                    cariByNIM();
                    break;
                case 3:
                    cout << "Kembali Ke Menu Utama" << endl;
                    break;
                default:
                    cout << "Pilihan Tidak Valid" << endl;
                    break;
                }
            } while (pilihanCari != 3);
            break;
        case 7:
            cout << "Terima Kasih" << endl;
            break;
        default:
            cout << "Pilihan Tidak Valid" << endl;
            break;
        }
    } while (pilihan != 7);

    return 0;
}
