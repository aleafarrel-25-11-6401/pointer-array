#include <iostream>
#include <string>
using namespace std;

#define MAX 10 // Batas maksimal antrian mahasiswa

// Struct data mahasiswa (TIDAK ADA PERUBAHAN)
struct Mahasiswa {
	string nama;
	string nim;
	int jumlahNilai;
	int nilai[10];
	float rataRata;
	char nilaiHuruf;
};

// ==============================================
// Variabel Global untuk Queue (Disamakan dengan kaidah dokumen)
// ==============================================
Mahasiswa antrian[MAX]; // Menggantikan 'tumpukan'
int head = 0;           // Sesuai dokumen, head di indeks 0 tidak berubah-ubah
int tail = 0;           // Sesuai dokumen: inisialisasi awal dan kondisi kosong tail = 0

// Fungsi menghitung rata-rata (TIDAK ADA PERUBAHAN)
float hitungRata(int *p, int n){
	float total = 0; 
	for (int i = 0; i < n; i++){
		total += *(p + i);
	}
	return total / n;
}

// Fungsi untuk mengubah nilai rata-rata menjadi huruf (TIDAK ADA PERUBAHAN)
char tentukanHuruf(float rata){
	if (rata >= 85) return 'A';
	else if (rata >= 70) return 'B';
	else if (rata >= 60) return 'C';
	else return 'D';
}

// ==============================================
//           FUNGSI-FUNGSI QUEUE
// ==============================================

// ENQUEUE (Menambah Data ke Antrian - setara Push)
void enqueue() {
	// Sesuai dokumen: mengecek apakah nilai Tail = MAX (berarti sudah penuh)
	if (tail == MAX) {
		cout << "Antrian Penuh! Tidak bisa menambah data." << endl;
		return;
	}

	cout << "\n--- Input Data Mahasiswa ---" << endl;
	cin.ignore(); 
	cout << "Masukkan Nama Mahasiswa : ";
	getline(cin, antrian[tail].nama); // Langsung menggunakan indeks tail saat ini (dimulai dari 0)
	cout << "Masukkan Nim Mahasiswa  : ";
	getline(cin, antrian[tail].nim);
	cout << "Masukkan Jumlah Nilai   : ";
	cin >> antrian[tail].jumlahNilai;
	
	int* p = antrian[tail].nilai; 
	
	for (int i = 0; i < antrian[tail].jumlahNilai; i++) {
		cout << "Masukkan Nilai ke-" << i + 1 << " = ";
		cin >> *(p + i);
	}
	
	// Proses perhitungan
	antrian[tail].rataRata = hitungRata(p, antrian[tail].jumlahNilai);
	antrian[tail].nilaiHuruf = tentukanHuruf(antrian[tail].rataRata);
	
	// Tail di-increment SETELAH data diisi. 
	// Jika dari 0, setelah diisi maka tail maju ke 1, dst.
	tail++; 
	
	cout << ">> Data berhasil di-ENQUEUE ke dalam Antrian! <<" << endl;
}

// DEQUEUE (Menghapus Data Terdepan dari Antrian - setara Pop)
void dequeue() {
	// Sesuai dokumen: Jika Tail = 0 maka kosong
	if (tail == 0) {
		cout << "Antrian Kosong! Tidak ada data yang bisa di-DEQUEUE." << endl;
	} else {
		// Menghapus elemen terdepan (head)
		cout << ">> Data Mahasiswa bernama '" << antrian[head].nama << "' berhasil di-DEQUEUE (Selesai antri)! <<" << endl;
		
		// Sesuai dokumen: Menggeser semua elemen antrian kedepan menggunakan looping
		for (int i = head; i < tail - 1; i++) {
			antrian[i] = antrian[i + 1];
		}
		
		// Sesuai dokumen: Mengurangi Tail dgn 1
		tail--; 
	}
}

// TAMPILKAN (Melihat isi Antrian)
void tampilkan() {
	// Sesuai dokumen: Jika Tail = 0 maka kosong
	if (tail == 0) {
		cout << "Antrian Kosong! Belum ada data." << endl;
		return;
	}

	cout << "\n==== Data Seluruh Mahasiswa (Dari Paling Depan) ====" << endl;
	// Sesuai dokumen: Menggunakan looping dari head s/d tail
	for(int k = head; k < tail; k++){
		cout << "Nama Mahasiswa  : " << antrian[k].nama << endl;
		cout << "NIM Mahasiswa   : " << antrian[k].nim << endl;
		
		int* p = antrian[k].nilai;
		for (int i = 0; i < antrian[k].jumlahNilai; i++) {
			cout << "Nilai ke-" << i + 1 << "\t= " << *(p + i) << endl;
		}

		cout << "Rata-rata nilai = " << antrian[k].rataRata << endl;
		cout << "Nilai Huruf     = " << antrian[k].nilaiHuruf << endl;
		cout << "--------------------------------" << endl;
	}
}

// CLEAR (Membersihkan seluruh Antrian)
void bersihkan() {
	tail = 0; // Sesuai inisialisasi dokumen, kembali ke 0
    cout << "=============================================" << endl;
	cout << ">> Semua data dalam Antrian telah dibersihkan! <<" << endl;
    cout << "=============================================" << endl;
}

// ==============================================
//                 PROGRAM UTAMA
// ==============================================

int main(){
	int pilihan;
	
	do {
		// Mengubah teks menu dari Stack menjadi Queue
		cout << "\n=== MENU ANTRIAN (QUEUE) MAHASISWA ===" << endl;
		cout << "1. Enqueue (Tambah Antrian)" << endl;
		cout << "2. Dequeue (Proses/Hapus Antrian Terdepan)" << endl;
		cout << "3. Tampilkan Data" << endl;
		cout << "4. Clear (Bersihkan Antrian)" << endl;
		cout << "5. Keluar" << endl;
		cout << "Pilih menu (1-5): ";
		cin >> pilihan;
		
		switch(pilihan){
			case 1: enqueue(); break;
			case 2: dequeue(); break;
			case 3: tampilkan(); break;
			case 4: bersihkan(); break;
			case 5: cout << "Keluar dari program. Terima kasih!" << endl; break;
			default: cout << "Pilihan tidak valid, coba lagi!" << endl;
		}
	} while(pilihan != 5);

	return 0;	
}
