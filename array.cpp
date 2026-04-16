#include <iostream>
#include <string>
using namespace std;

// 1. Tambahkan Struct pada data mahasiswa
struct Mahasiswa {
	string nama;
	string nim;
	int jumlahNilai;
	int nilai[10];
	float rataRata;
	char nilaiHuruf;
};

float hitungRata(int *p, int n){
	// Wadah penampung total (perbaikan: inisialisasi awal dengan 0)
	float total = 0; 

	// Tambahkan semua value dari array
	for (int i = 0; i < n; i++){
		total += *(p + i);
	}

	// Kembalikan hasil rata-rata ke main
	return total / n;
}

// 4. Fungsi untuk mengubah nilai rata-rata menjadi huruf
char tentukanHuruf(float rata){
	if (rata >= 85) return 'A';
	else if (rata >= 70) return 'B';
	else if (rata >= 60) return 'C';
	else return 'D';
}

int main(){
	int jumlahMhs;
	
	// 2. Input lebih dari 1 mahasiswa
	cout << "Masukkan Jumlah Mahasiswa yang ingin diinput: ";
	cin >> jumlahMhs;
	cin.ignore(); // Membersihkan sisa buffer enter agar getline di bawah bisa berjalan

	// Deklarasi array struct
	Mahasiswa mhs[50];

	cout << endl;
	// Looping untuk input tiap mahasiswa
	for(int k = 0; k < jumlahMhs; k++){
		cout << "--- Input Data Mahasiswa Ke-" << k + 1 << " ---" << endl;
		cout << "Masukkan Nama Mahasiswa : ";
		getline(cin, mhs[k].nama);
		cout << "Masukkan Nim Mahasiswa  : ";
		getline(cin, mhs[k].nim);
		cout << "Masukkan Jumlah Nilai   : ";
		cin >> mhs[k].jumlahNilai;
		
		// Menghubungkan pointer ke array nilai dari mahasiswa ke-k
		int* p = mhs[k].nilai;
		
		// Input nilai sesuai jumlah (n)
		for (int i = 0; i < mhs[k].jumlahNilai; i++) {
			cout << "Masukkan Nilai ke-" << i + 1 << " = ";
			cin >> *(p + i);
		}
		
		// Proses perhitungan langsung disimpan dalam struct
		mhs[k].rataRata = hitungRata(p, mhs[k].jumlahNilai);
		mhs[k].nilaiHuruf = tentukanHuruf(mhs[k].rataRata);
		
		cin.ignore(); // Membersihkan buffer lagi sebelum looping mahasiswa berikutnya
		cout << endl;
	}
	
	// 3. Menampilkan output SEMUA data mahasiswa
	cout << "==== Data Seluruh Mahasiswa ====" << endl;
	for(int k = 0; k < jumlahMhs; k++){
		cout << "Mahasiswa Ke-" << k + 1 << ":" << endl;
		cout << "Nama Mahasiswa  : " << mhs[k].nama << endl;
		cout << "NIM Mahasiswa   : " << mhs[k].nim << endl;
		
		int* p = mhs[k].nilai;
		for (int i = 0; i < mhs[k].jumlahNilai; i++) {
			cout << "Nilai ke-" << i + 1 << "\t= " << *(p + i) << endl;
		}

		cout << "Rata-rata nilai = " << mhs[k].rataRata << endl;
		cout << "Nilai Huruf     = " << mhs[k].nilaiHuruf << endl;
		cout << "--------------------------------" << endl;
	}

	return 0;	
}
