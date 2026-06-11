#include <iostream>
#include <string>
#include <cstdlib>

// Membatasi jumlah maksimal antrean agar memori tidak overload (konsep Queue)
#define MAX 10

using namespace std;

// Struktur Mahasiswa sebagai Node Linked List
// Setiap node menyimpan data mahasiswa dan pointer ke node berikutnya
struct Mahasiswa {
    string nama;
    string nim;
    int jumlahNilai;
    int nilai[MAX];    // Array untuk menyimpan daftar nilai
    float rataRata;
    char nilaiHuruf;
    Mahasiswa* next;   // Pointer 'next' untuk menunjuk ke alamat node selanjutnya di memori
};

// === Pointer Global untuk manajemen Linked List ===
Mahasiswa* head = NULL; // 'head' selalu menunjuk ke node pertama dalam urutan
Mahasiswa* tail = NULL; // 'tail' selalu menunjuk ke node terakhir untuk mempermudah Enqueue
int countQueue = 0;    // Variabel pembantu untuk menghitung berapa banyak data yang ada

// Fungsi Hitung Rata-Rata
// Menggunakan pointer '*ptrNilai' untuk mengakses elemen array secara langsung
float hitungRataRata(int* ptrNilai, int jumlah){
    float total = 0;

    for (int i = 0; i < jumlah; i++){
        // Menggunakan dereference operator (*) untuk mengambil nilai di alamat memori
        total += *(ptrNilai + i); 
    }

    // Hindari pembagian dengan nol jika data kosong
    return (jumlah > 0) ? total / jumlah : 0;
}

// Fungsi Tukar Data (Bantuan untuk Sorting)
// Fungsi ini menukar konten/isi data antar dua node, namun membiarkan pointer 'next' tetap
// agar struktur rantai Linked List tidak rusak.
void tukarData(Mahasiswa* nodeA, Mahasiswa* nodeB) {
    // Simpan dulu alamat 'next' masing-masing agar tidak hilang saat di-copy
    Mahasiswa* nextA = nodeA->next; 
    Mahasiswa* nextB = nodeB->next;

    // Lakukan copy seluruh isi struct dari nodeB ke nodeA (termasuk next-nya sementara)
    Mahasiswa temp = *nodeA;
    *nodeA = *nodeB;
    *nodeB = temp;

    // Kembalikan alamat 'next' ke posisi semula agar urutan list tetap benar
    nodeA->next = nextA;
    nodeB->next = nextB;
}

// Fungsi Tentukan Nilai Huruf berdasarkan standar akademik
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

// === Fungsi Pengecekan Status Antrean ===

// Cek apakah antrean sudah penuh sesuai batas MAX
bool isFull(){
    return (countQueue >= MAX);
}

// Cek apakah antrean masih kosong (head masih NULL)
bool isEmpty(){
    return (head == NULL);
}

// === Fungsi Enqueue (Tambah Data Baru ke Akhir Antrean) ===
void enqueue(){
    // Validasi apakah antrean sudah penuh
    if (isFull()){
        cout << "\n==== Antrean Penuh! Tidak bisa menambah data lagi ====" << endl;
        return;
    } else {
        // 'new Mahasiswa()' mengalokasikan memori baru di Heap secara dinamis
        Mahasiswa* nodeBaru = new Mahasiswa();

        cout << "\n==== Input Data Mahasiswa Baru ====" << endl;
        cout << "Masukkan Nama Mahasiswa : ";
        getline(cin, nodeBaru->nama);
        cout << "Masukkan NIM Mahasiswa  : ";
        getline(cin, nodeBaru->nim);
        cout << "Masukkan Jumlah Nilai   : ";
        cin >> nodeBaru->jumlahNilai;

        cout << "\n";

        // Mengambil alamat awal array nilai untuk diproses oleh pointer
        int* ptrNilai = nodeBaru->nilai;

        for (int i = 0; i < nodeBaru->jumlahNilai; i++){
            cout << "Masukkan Nilai ke-" << i + 1 << " = ";
            // Input langsung ke alamat memori yang ditunjuk pointer
            cin >> *(ptrNilai + i);
        }
        cin.ignore(); // Membersihkan sisa newline di buffer input

        // Hitung rata-rata dan tentukan grade
        nodeBaru->rataRata = hitungRataRata(ptrNilai, nodeBaru->jumlahNilai);
        nodeBaru->nilaiHuruf = tentukanNilaiHuruf(nodeBaru->rataRata);
        
        // Karena ini Enqueue (tambah di belakang), node baru ini menunjuk ke NULL
        nodeBaru->next = NULL; 

        // Atur posisi head dan tail
        if (isEmpty()){
            // Jika list kosong, maka node baru adalah yang pertama sekaligus terakhir
            head = nodeBaru;
            tail = nodeBaru;
        } else {
            // Sambungkan node terakhir saat ini ke node baru
            tail->next = nodeBaru; 
            // Pindahkan penanda 'tail' ke node baru tersebut
            tail = nodeBaru;       
        }

        countQueue++; // Tambah jumlah total data
        cout << "\n==== Data Berhasil Ditambahkan ke Antrean ====" << endl;
    }
}

// === Fungsi Dequeue (Hapus Data Terdepan/Pertama) ===
void dequeue(){
    if (isEmpty()){
        cout << "\n==== Antrean Kosong! Tidak ada data untuk dihapus ====" << endl;
    } else {
        // Simpan alamat node yang akan dihapus agar bisa di-'delete' nanti
        Mahasiswa* hapus = head; 
        cout << "\n==== Data Mahasiswa: -- " << hapus->nama << " -- Berhasil Dihapus (Keluar Antrean) ====" << endl;
        
        // Pindahkan 'head' ke node berikutnya agar node pertama terlepas dari list
        head = head->next; 
        
        // Bebaskan memori yang digunakan oleh node lama agar tidak terjadi memory leak
        delete hapus;      
        countQueue--;

        // Jika setelah dihapus list jadi kosong, pastikan tail juga NULL
        if (head == NULL){
            tail = NULL;
        }
    }
}

// === Fungsi Tampilkan (Cetak Seluruh Isi Linked List) ===
void tampilkan(){
    if (isEmpty()){
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    } else {
        cout << "\n==== Daftar Seluruh Mahasiswa ====" << endl;

        // Gunakan pointer 'temp' untuk menelusuri list tanpa merusak posisi 'head'
        Mahasiswa* temp = head;
        
        // Loop selama pointer 'temp' belum mencapai ujung (NULL)
        while (temp != NULL){
            cout << "Nama\t\t : " << temp->nama << endl;
            cout << "NIM\t\t : " << temp->nim << endl;
            
            cout << "\n";

            int* ptrNilai = temp->nilai;

            for (int j = 0; j < temp->jumlahNilai; j++){
                // Menampilkan isi nilai menggunakan aritmatika pointer
                cout << "Nilai ke-" << j + 1 << "\t = " << *(ptrNilai + j) << endl;
            }

            cout << "\nNilai Rata-Rata\t = " << temp->rataRata << endl;
            cout << "Nilai Huruf\t = " << temp->nilaiHuruf << endl;
            cout << "--------------------------\n";

            // Pindahkan 'temp' ke node selanjutnya (Traversing)
            temp = temp->next; 
        }
    }
}

// === Fungsi Bersihkan (Hapus Semua Node & Kosongkan Memori) ===
void bersihkan(){
    if (isEmpty()){
        cout << "\n==== Antrean Sudah Kosong ====" << endl;
        return;
    } else {
        // Hapus satu per satu dari depan (head) sampai habis
        while (head != NULL){
            Mahasiswa* hapus = head;
            head = head->next;
            delete hapus;
        }
        // Reset status variabel global
        tail = NULL;
        countQueue = 0;
        cout << "\n==== Seluruh Data Telah Dihapus dari Memori ====" << endl;
    }    
}

// === Fungsi Sorting (Selection Sort - Descending berdasarkan Rata-Rata) ===
void urutkanSelection(){
    if (countQueue <= 1){
        cout << "\n==== Data Kurang, Minimal 2 Data Untuk Diurutkan ====" << endl;
    } else {
        // Loop luar: menentukan posisi node yang akan dibandingkan (i)
        for (Mahasiswa* i = head; i->next != NULL; i = i->next){
            Mahasiswa* maxNode = i;

            // Loop dalam: mencari nilai terbesar di sisa list (j)
            for (Mahasiswa* j = i->next; j != NULL; j = j->next){
                if (j->rataRata > maxNode->rataRata){
                    maxNode = j;
                }
            }

            // Jika ditemukan nilai yang lebih besar, tukar isi datanya
            if (maxNode != i){
                tukarData(i, maxNode);
            }
        }
        cout << "\n==== Data Berhasil Diurutkan Berdasarkan Nilai Tertinggi ====" << endl;
        tampilkan();
    }
}

// === Fungsi Cari Berdasarkan Nama (Linear Search) ===
void cariByNama() {
    if (isEmpty()) {
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    }

    string target;
    cout << "Masukkan Nama yang ingin dicari: ";
    getline(cin, target);

    Mahasiswa* temp = head;
    bool ditemukan = false;

    // Telusuri list satu per satu (Linear Search)
    while (temp != NULL) {
        if (temp->nama == target) {
            cout << "\n==== Data Ditemukan! ====" << endl;
            cout << "Nama\t\t : " << temp->nama << endl;
            cout << "NIM\t\t : " << temp->nim << endl;
            cout << "Nilai Rata-Rata\t = " << temp->rataRata << endl;
            cout << "Nilai Huruf\t = " << temp->nilaiHuruf << endl;
            cout << "--------------------------" << endl;
            ditemukan = true;
            break; // Berhenti jika sudah ketemu
        }
        temp = temp->next; // Geser ke node berikutnya
    }

    if (!ditemukan) {
        cout << "\n==== Data dengan Nama [" << target << "] Tidak Ditemukan ====" << endl;
    }
}

// === Fungsi Cari Berdasarkan NIM (Linear Search) ===
void cariByNIM() {
    if (isEmpty()) {
        cout << "\n==== Antrean Kosong ====" << endl;
        return;
    }

    string target;
    cout << "Masukkan NIM yang ingin dicari: ";
    getline(cin, target);

    Mahasiswa* temp = head;
    bool ditemukan = false;

    while (temp != NULL) {
        if (temp->nim == target) {
            cout << "\n==== Data Ditemukan! ====" << endl;
            cout << "Nama\t\t : " << temp->nama << endl;
            cout << "NIM\t\t : " << temp->nim << endl;
            cout << "Nilai Rata-Rata\t = " << temp->rataRata << endl;
            cout << "Nilai Huruf\t = " << temp->nilaiHuruf << endl;
            cout << "--------------------------" << endl;
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "\n==== Data dengan NIM [" << target << "] Tidak Ditemukan ====" << endl;
    }
}

int main(){
    int pilihanMenu;
    do {
        // Tampilan Antarmuka Menu Utama
        cout << "\n======================================" << endl;
        cout << "   SISTEM MANAJEMEN NILAI MAHASISWA   " << endl;
        cout << "======================================" << endl;
        cout << "1. Input Data (Enqueue)" << endl;
        cout << "2. Hapus Data (Dequeue)" << endl;
        cout << "3. Tampilkan Semua Data" << endl;
        cout << "4. Kosongkan Semua Data" << endl;
        cout << "5. Urutkan (Selection Sort - DESC)" << endl;
        cout << "6. Pencarian Data (Linear Search)" << endl;
        cout << "7. Keluar Program" << endl;
        cout << "--------------------------------------" << endl;

        cout << "Masukkan Pilihan Anda (1-7) : ";
        cin >> pilihanMenu;
        cin.ignore(); // Bersihkan buffer enter

        switch (pilihanMenu)
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
            // Menu Pencarian (Sub-Menu)
            int pilihanCari;
            do {
                cout << "\n==== MENU PENCARIAN ====" << endl;
                cout << "1. Cari Berdasarkan Nama" << endl;
                cout << "2. Cari Berdasarkan NIM" << endl;
                cout << "3. Kembali ke Menu Utama" << endl;
                cout << "Masukkan Pilihan : ";
                cin >> pilihanCari;
                cin.ignore();

                if (pilihanCari == 1) cariByNama();
                else if (pilihanCari == 2) cariByNIM();
                else if (pilihanCari != 3) cout << "Pilihan tidak valid!" << endl;

            } while (pilihanCari != 3);
            break;
        case 7:
            cout << "Selesai. Keluar dari program..." << endl;
            break;
        default:
            cout << "Pilihan tidak ada dalam menu!" << endl;
            break;
        }
    } while (pilihanMenu != 7);

    return 0;
}
