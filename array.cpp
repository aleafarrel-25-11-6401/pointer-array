#include <iostream>
#include <string>
using namespace std;

#define MAX 10 // Batas maksimal tumpukan mahasiswa

// Struct data mahasiswa
struct Mahasiswa {
	string nama;
	string nim;
	int jumlahNilai;
	int nilai[10];
	float rataRata;
	char nilaiHuruf;
};

// Variabel Global untuk Stack
Mahasiswa tumpukan[MAX];
int top = -1; // -1 menandakan stack sedang kosong

// Fungsi menghitung rata-rata
float hitungRata(int *p, int n){
	float total = 0; 
	for (int i = 0; i < n; i++){
		total += *(p + i);
	}
	return total / n;
}

// Fungsi untuk mengubah nilai rata-rata menjadi huruf
char tentukanHuruf(float rata){
	if (rata >= 85) return 'A';
	else if (rata >= 70) return 'B';
	else if (rata >= 60) return 'C';
	else return 'D';
}

// ==============================================
//           FUNGSI-FUNGSI STACK
// ==============================================

// PUSH (Menambah Data ke Stack)
void push() {
	if (top >= MAX - 1) {
		cout << "Stack Penuh! Tidak bisa menambah data." << endl;
		return;
	}

	top++; // Naikkan posisi tumpukan teratas
	
	cout << "\n--- Input Data Mahasiswa ---" << endl;
	cin.ignore(); // Membersihkan sisa buffer dari menu sebelumnya
	cout << "Masukkan Nama Mahasiswa : ";
	getline(cin, tumpukan[top].nama);
	cout << "Masukkan Nim Mahasiswa  : ";
	getline(cin, tumpukan[top].nim);
	cout << "Masukkan Jumlah Nilai   : ";
	cin >> tumpukan[top].jumlahNilai;
	
	int* p = tumpukan[top].nilai; // Menghubungkan pointer ke array nilai
	
	for (int i = 0; i < tumpukan[top].jumlahNilai; i++) {
		cout << "Masukkan Nilai ke-" << i + 1 << " = ";
		cin >> *(p + i);
	}
	
	// Proses perhitungan
	tumpukan[top].rataRata = hitungRata(p, tumpukan[top].jumlahNilai);
	tumpukan[top].nilaiHuruf = tentukanHuruf(tumpukan[top].rataRata);
	
	cout << ">> Data berhasil di-PUSH ke dalam Stack! <<" << endl;
}

// POP (Menghapus Data Teratas dari Stack)
void pop() {
	if (top == -1) {
		cout << "Stack Kosong! Tidak ada data yang bisa di-POP." << endl;
	} else {
		cout << ">> Data Mahasiswa bernama '" << tumpukan[top].nama << "' berhasil di-POP (Dihapus)! <<" << endl;
		top--; // Menghapus cukup dengan menurunkan indikator top
	}
}

// TAMPILKAN (Melihat isi Stack)
void tampilkan() {
	if (top == -1) {
		cout << "Stack Kosong! Belum ada data." << endl;
		return;
	}

	cout << "\n==== Data Seluruh Mahasiswa (Dari Paling Atas) ====" << endl;
	// Looping mundur karena sifat Stack (Last In First Out)
	for(int k = top; k >= 0; k--){
		cout << "Nama Mahasiswa  : " << tumpukan[k].nama << endl;
		cout << "NIM Mahasiswa   : " << tumpukan[k].nim << endl;
		
		int* p = tumpukan[k].nilai;
		for (int i = 0; i < tumpukan[k].jumlahNilai; i++) {
			cout << "Nilai ke-" << i + 1 << "\t= " << *(p + i) << endl;
		}

		cout << "Rata-rata nilai = " << tumpukan[k].rataRata << endl;
		cout << "Nilai Huruf     = " << tumpukan[k].nilaiHuruf << endl;
		cout << "--------------------------------" << endl;
	}
}

// CLEAR (Membersihkan seluruh Stack)
void bersihkan() {
	top = -1; // Cukup kembalikan top ke -1
    cout << "=============================================" << endl;
	cout << ">> Semua data dalam Stack telah dibersihkan! <<" << endl;
    cout << "=============================================" << endl;
}

// ==============================================
//                 PROGRAM UTAMA
// ==============================================

int main(){
	int pilihan;
	
	do {
		cout << "\n=== MENU STACK MAHASISWA ===" << endl;
		cout << "1. Push (Tambah Data)" << endl;
		cout << "2. Pop (Hapus Data Teratas)" << endl;
		cout << "3. Tampilkan Data" << endl;
		cout << "4. Clear (Bersihkan Stack)" << endl;
		cout << "5. Keluar" << endl;
		cout << "Pilih menu (1-5): ";
		cin >> pilihan;
		
		switch(pilihan){
			case 1: push(); break;
			case 2: pop(); break;
			case 3: tampilkan(); break;
			case 4: bersihkan(); break;
			case 5: cout << "Keluar dari program. Terima kasih!" << endl; break;
			default: cout << "Pilihan tidak valid, coba lagi!" << endl;
		}
	} while(pilihan != 5);

	return 0;	
}
