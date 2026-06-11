#include <iostream>
#include <string>
#include <cstdlib>
#define MAX 10

using namespace std;

// Struktur Mahasiswa sebagai Node Linked List
struct Mahasiswa {
    string nama;
    string nim;
    int jumlahNilai;
    int nilai[MAX];
    float rataRata;
    char nilaiHuruf;
    Mahasiswa* next; // Pointer untuk menunjuk ke node selanjutnya
};

// Pointer Global untuk manajemen Linked List
Mahasiswa* head = NULL; // Menunjuk ke node pertama
Mahasiswa* tail = NULL; // Menunjuk ke node terakhir
int countQueue = 0;    // Melacak jumlah node (pengganti index pada array)

// Fungsi Hitung Rata-Rata
float rataRata(int* p, int n){
    float total = 0;

    for (int i = 0; i < n; i++){
        total += *(p + i);
    }

    return (n > 0) ? total / n : 0;
}

// Fungsi Tukar Data (Bantuan untuk Sorting Linked List)
// Menukar isi data antar dua node tanpa mengubah alamat/pointer next-nya
void tukarData(Mahasiswa* a, Mahasiswa* b) {
    Mahasiswa* nextA = a->next; // Simpan pointer next asli
    Mahasiswa* nextB = b->next;

    // Lakukan copy seluruh isi struct
    Mahasiswa temp = *a;
    *a = *b;
    *b = temp;

    // Kembalikan pointer next ke posisi semula agar rantai list tidak rusak
    a->next = nextA;
    b->next = nextB;
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
    // Cek berdasarkan jumlah node yang sudah dialokasikan
    if (countQueue >= MAX){
        return true;
    } else {
        return false;
    }
}

bool isEmpty(){
    // Jika head NULL berarti tidak ada data sama sekali
    if (head == NULL){
        return true;
    } else {
        return false;
    }
}

// === Fungsi Enqueue (Tambah Data di Akhir) ===
void enqueue(){
    if (isFull()){
        cout << "\n==== Antrean Penuh ====" << endl;
        return;
    } else {
        // Alokasi memori dinamis untuk node baru
        Mahasiswa* nodeBaru = new Mahasiswa();

        cout << "\n==== Input Data ====" << endl;
        cout << "Masukkan Nama Mahasiswa : ";
        getline(cin, nodeBaru->nama);
        cout << "Masukkan NIM Mahasiswa : ";
        getline(cin, nodeBaru->nim);
        cout << "Masukkan Jumlah Nilai : ";
        cin >> nodeBaru->jumlahNilai;

        cout << "\n";

        int* p = nodeBaru->nilai;

        for (int i = 0; i < nodeBaru->jumlahNilai; i++){
            cout << "Masukkan Nilai ke-" << i + 1 << " = ";
            cin >> *(p + i);
        }
        cin.ignore();

        nodeBaru->rataRata = rataRata(p, nodeBaru->jumlahNilai);
        nodeBaru->nilaiHuruf = tentukanNilaiHuruf(nodeBaru->rataRata);
        nodeBaru->next = NULL; // Node baru akan jadi node terakhir

        // Hubungkan node baru ke dalam list
        if (isEmpty()){
            head = nodeBaru;
            tail = nodeBaru;
        } else {
            tail->next = nodeBaru; // Sambungkan dari ekor lama
            tail = nodeBaru;       // Geser penanda ekor ke node baru
        }

        countQueue++;
        cout << "\n==== Data Berhasil Ditambahkan ====" << endl;
    }
}

// === Fungsi Dequeue (Hapus Data di Awal) ===
void dequeue(){
    if (isEmpty()){
        cout << "\n==== Antrean Kosong ====" << endl;
    } else {
        Mahasiswa* hapus = head; // Simpan alamat node yang akan dihapus
        cout << "\n==== Data Mahasiswa Bernama -- " << hapus->nama << " -- Berhasil Dihapus ====" << endl;
        
        head = head->next; // Geser head ke node selanjutnya
        delete hapus;      // Bebaskan memori node yang dihapus
        countQueue--;

        // Jika list menjadi kosong setelah penghapusan
        if (head == NULL){
            tail = NULL;
        }
    }
}

// === Fungsi Tampilkan (Traversing Linked List) ===
void tampilkan(){
    if (isEmpty()){
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    } else {
        cout << "\n==== Data Saat Ini ====" << endl;

        // Gunakan pointer bantuan untuk menelusuri list dari head
        Mahasiswa* curr = head;
        while (curr != NULL){
            cout << "Nama\t\t : " << curr->nama << endl;
            cout << "NIM\t\t : " << curr->nim << endl;
            
            cout << "\n";

            int* p = curr->nilai;

            for (int j = 0; j < curr->jumlahNilai; j++){
                cout << "Nilai ke-" << j + 1 << "\t = " << *(p + j) << endl;
            }

            cout << "\nNilai Rata-Rata\t = " << curr->rataRata << endl;
            cout << "Nilai Huruf\t = " << curr->nilaiHuruf << endl;
            cout << "--------------------------\n";

            curr = curr->next; // Pindah ke node selanjutnya
        }
    }
}

// === Fungsi Bersihkan (Hapus Semua Node & Free Memory) ===
void bersihkan(){
    if (isEmpty()){
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    } else {
        // Hapus satu per satu sampai head NULL
        while (head != NULL){
            Mahasiswa* hapus = head;
            head = head->next;
            delete hapus;
        }
        tail = NULL;
        countQueue = 0;
        cout << "\n==== Seluruh Data Dibersihkan ====" << endl;
    }    
}

// === Fungsi Sorting Berdasarkan Rata-Rata (Selection Sort pada Linked List) ===
void urutkanSelection(){
    if (countQueue <= 1){
        cout << "\n==== Belum Cukup Data Untuk Diurutkan ====" << endl;
    } else {
        // Loop i sebagai pointer acuan (seperti index i pada array)
        for (Mahasiswa* i = head; i->next != NULL; i = i->next){
            Mahasiswa* maxNode = i;

            // Loop j mencari nilai terbesar di sisa list
            for (Mahasiswa* j = i->next; j != NULL; j = j->next){
                if (j->rataRata > maxNode->rataRata){
                    maxNode = j;
                }
            }

            // Jika ditemukan yang lebih besar, tukar isinya
            if (maxNode != i){
                tukarData(i, maxNode);
            }
        }
        cout << "\n==== Data berhasil diurutkan berdasarkan Rata-Rata ====" << endl;
        tampilkan();
    }
}

// === Fungsi Sorting Berdasarkan Nama (ASC) ===
void urutkanByNama() {
    if (isEmpty()) return;
    for (Mahasiswa* i = head; i->next != NULL; i = i->next) {
        Mahasiswa* minNode = i;
        for (Mahasiswa* j = i->next; j != NULL; j = j->next) {
            if (j->nama < minNode->nama) {
                minNode = j;
            }
        }
        if (minNode != i) tukarData(i, minNode);
    }
}

// === Fungsi Sorting Berdasarkan NIM (ASC) ===
void urutkanByNIM() {
    if (isEmpty()) return;
    for (Mahasiswa* i = head; i->next != NULL; i = i->next) {
        Mahasiswa* minNode = i;
        for (Mahasiswa* j = i->next; j != NULL; j = j->next) {
            if (j->nim < minNode->nim) {
                minNode = j;
            }
        }
        if (minNode != i) tukarData(i, minNode);
    }
}

// === Fungsi Cari Berdasarkan Nama (Linear Search pada Linked List) ===
void cariByNama() {
    if (isEmpty()) {
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    }

    string cari;
    cout << "Masukkan Nama yang dicari: ";
    getline(cin, cari);

    Mahasiswa* curr = head;
    bool found = false;

    // Telusuri satu per satu sampai ketemu atau sampai list habis
    while (curr != NULL) {
        if (curr->nama == cari) {
            cout << "\n==== Data --" << cari << "-- Ditemukan (Hasil Linear Search) ====" << endl;
            cout << "Nama\t\t : " << curr->nama << endl;
            cout << "NIM\t\t : " << curr->nim << endl;
            cout << "Nilai Rata-Rata\t = " << curr->rataRata << endl;
            cout << "Nilai Huruf\t = " << curr->nilaiHuruf << endl;
            cout << "--------------------------" << endl;
            found = true;
            break;
        }
        curr = curr->next;
    }

    if (!found) {
        cout << "\n==== Data dengan Nama --" << cari << "-- Tidak Ditemukan ====" << endl;
    }
}

// === Fungsi Cari Berdasarkan NIM (Linear Search pada Linked List) ===
void cariByNIM() {
    if (isEmpty()) {
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    }

    string cari;
    cout << "Masukkan NIM yang dicari: ";
    getline(cin, cari);

    Mahasiswa* curr = head;
    bool found = false;

    while (curr != NULL) {
        if (curr->nim == cari) {
            cout << "\n==== Data --" << cari << "-- Ditemukan (Hasil Linear Search) ====" << endl;
            cout << "Nama\t\t : " << curr->nama << endl;
            cout << "NIM\t\t : " << curr->nim << endl;
            cout << "Nilai Rata-Rata\t = " << curr->rataRata << endl;
            cout << "Nilai Huruf\t = " << curr->nilaiHuruf << endl;
            cout << "--------------------------" << endl;
            found = true;
            break;
        }
        curr = curr->next;
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
            system("cls");               
        
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
