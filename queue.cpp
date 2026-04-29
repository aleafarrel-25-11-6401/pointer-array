#include <iostream>
#include <string>
using namespace std;

float hitungRata(int *p, int n){
	// Wadah penampung total
	float total;

	// Tambahkan semua value dari array
	for (int i = 0; i < n; i++){
		total += *(p + i);
	}

	// Kembalikan hasil rata-rata ke main
	return total / n;
}

int main(){
	string nama, nim;
	int nilai[10];

	// Menghubungkan pointer ke array
	int* p = nilai;

	// Indeks dan jumlah nilai
	int i, n;

	cout << endl;
	cout << "Masukkan Nama Mahasiswa : ";
	getline(cin, nama);
	cout << "Masukkan Nim Mahasiswa : ";
	getline(cin, nim);
	cout << "Masukkan Jumlah Nilai : ";
	cin >> n;
	cout << endl;
	
	// Input nilai sesuai jumlah (n)
	for (i = 0; i < n; i++) {
		cout << "Masukkan Nilai ke-" << i + 1 << " = ";
		cin >> *(p + i);
	}
	
	// Menampilkan output data
	cout << endl;
	cout << "==== Data Mahasiswa ====" << endl;
	cout << "Nama Mahasiswa : " << nama << endl;
	cout << "NIM Mahasiswa : " << nim << endl;
	
	for (i = 0; i < n; i++) {
		cout << "Nilai ke-" << i + 1 << " = " << *(p + i);
		cout << endl;
	}

	// Hitung rata-rata menggunakan 
	float hasilratarata = hitungRata(p,n);
	cout << "Rata-rata nilai = " << hasilratarata << endl;

return 0;	
}
	
