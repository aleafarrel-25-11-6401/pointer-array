#include <iostream>
#include <string>

using namespace std;

float ratarata(int *p , int n){
	float total = 0; // Variabel penampung total nilai

	// Tambah semua nilai yang ada di array
	for (int i = 0; i < n; i++){
		total += *(p + i);
	}

	// Cari rata-rata dan kembalikan hasilnya
	return total / n;
}

int main (){
	string nama, nim; // String untuk Nama dan NIM mahasiswa
	int i, n; // Variable global untuk looping dan jumlah nilai

	// ==== Input Data ====
	cout << endl;
	cout << "Masukkan Nama Mahasiswa\t" << ": ";
	getline(cin, nama); // getline() agar bisa menggunakan spasi
	cout << "Masukkan NIM Mahasiswa\t" << ": ";
	getline(cin, nim);
	cout << "Masukkan Jumlah Nilai\t" << ": ";
	cin >> n;
	
	cout << endl;
	
	// ==== Array ====
	int *p = new int[n]; // Alokasi memori untuk array nilai dengan ukuran n

	// ==== Input Nilai ke Array ====
	for (i = 0; i < n; i++) {
		cout << "Masukkan Nilai ke-" << i + 1 << " = ";
		cin >> *(p + i);
	}
	
	// Cari rata-rata menggunakan fungsi ratarata()
	float rataratanilai = ratarata(p, n);

	cout << endl;
	cout << endl;

	// ==== Output Data ====
	cout << "==== Data Mahasiswa ====\n\n";
	cout << "Nama Mahasiswa\t" << ": " << nama << endl;
	cout << "NIM Mahasiswa\t" << ": " << nim << endl;
	cout << endl;

	for (i = 0; i < n; i++) {
		cout << "Nilai ke-" << i + 1 << " = " << *(p + i) << endl;
	}
	cout << endl;
	cout << "Rata-rata nilai\t" << ": " << rataratanilai << endl;
	cout << endl;
	
	delete[] p; // Dealokasi memori yang telah digunakan untuk array
	return 0;
}
