#include <iostream>
#include <string>
using namespace std;

#define MAX 10 // batas maksimal isi antrian

// struktur data untuk menyimpan info mahasiswa
struct Mahasiswa {
	string nama;
	string nim;
	int jumlahNilai;
	int nilai[10];
	float rataRata;
	char nilaiHuruf;
};

Mahasiswa antrian[MAX];
int head = 0; // index paling depan
int tail = 0; // index paling belakang/kosong

// fungsi bantu untuk menghitung rata-rata
float hitungRata(int *p, int n){
	float total = 0; 
	for (int i = 0; i < n; i++){
		total += *(p + i);
	}
	return total / n;
}

// fungsi bantu untuk menentukan nilai huruf
char tentukanHuruf(float rata){
	if (rata >= 85) return 'A';
	else if (rata >= 70) return 'B';
	else if (rata >= 60) return 'C';
	else return 'D';
}

// menambah data baru ke antrian (enqueue)
void enqueue() {
	if (tail == MAX) {
		cout << "Antrian penuh!\n";
		return;
	}

	cout << "\n-- Input Data --\n";
	cin.ignore(); 
	cout << "Nama mahasiswa : ";
	getline(cin, antrian[tail].nama); 
	cout << "NIM            : ";
	getline(cin, antrian[tail].nim);
	cout << "Jumlah nilai   : ";
	cin >> antrian[tail].jumlahNilai;
	
	int* p = antrian[tail].nilai; 
	
	for (int i = 0; i < antrian[tail].jumlahNilai; i++) {
		cout << "Nilai ke-" << i + 1 << " = ";
		cin >> *(p + i);
	}
	
	antrian[tail].rataRata = hitungRata(p, antrian[tail].jumlahNilai);
	antrian[tail].nilaiHuruf = tentukanHuruf(antrian[tail].rataRata);
	
	tail++; // geser tail tiap ada data masuk
	cout << "Data masuk antrian.\n";
}

// menghapus data paling depan (dequeue)
void dequeue() {
	if (tail == 0) {
		cout << "Antrian masih kosong.\n";
	} else {
		cout << "Mahasiswa atas nama " << antrian[head].nama << " berhasil dihapus.\n";
		
		// geser semua sisa antrian ke depan
		for (int i = head; i < tail - 1; i++) {
			antrian[i] = antrian[i + 1];
		}
		
		tail--; 
	}
}

// menampilkan seluruh isi antrian
void tampilkan() {
	if (tail == 0) {
		cout << "Antrian kosong.\n";
		return;
	}

	cout << "\n-- Data Antrian --\n";
	for(int k = head; k < tail; k++){
		cout << "Nama       : " << antrian[k].nama << endl;
		cout << "NIM        : " << antrian[k].nim << endl;
		
		int* p = antrian[k].nilai;
		for (int i = 0; i < antrian[k].jumlahNilai; i++) {
			cout << "Nilai " << i + 1 << "    = " << *(p + i) << endl;
		}

		cout << "Rata-rata  = " << antrian[k].rataRata << endl;
		cout << "Huruf      = " << antrian[k].nilaiHuruf << endl;
		cout << "-----------------------\n";
	}
}

// mengurutkan antrian berdasarkan nilai terbesar dengan Bubble Sort
void urutkanBubbleSort() {
    if (tail <= 1) {
        cout << "Data belum cukup untuk diurutkan.\n";
        return;
    }

    int n = tail - head; 
    for (int i = 0; i < n - 1; i++) {
        for (int j = head; j < tail - i - 1; j++) {
            // cek sebelahnya, kalau sebelahnya lebih gede, tukar posisinya
            if (antrian[j].rataRata < antrian[j + 1].rataRata) {
                Mahasiswa temp = antrian[j];
                antrian[j] = antrian[j + 1];
                antrian[j + 1] = temp;
            }
        }
    }
    cout << "Berhasil diurutkan dengan Bubble Sort.\n";
}

// mengurutkan antrian berdasarkan nilai terbesar dengan Selection Sort
void urutkanSelectionSort() {
    if (tail <= 1) {
        cout << "Data belum cukup untuk diurutkan.\n";
        return;
    }

    for (int i = head; i < tail - 1; i++) {
        int maxIndex = i; 
        
        // cari indeks dengan nilai rata-rata paling tinggi
        for (int j = i + 1; j < tail; j++) {
            if (antrian[j].rataRata > antrian[maxIndex].rataRata) {
                maxIndex = j;
            }
        }
        
        // tukar posisinya kalau ketemu yang lebih besar
        if (maxIndex != i) {
            Mahasiswa temp = antrian[i];
            antrian[i] = antrian[maxIndex];
            antrian[maxIndex] = temp;
        }
    }
    cout << "Berhasil diurutkan dengan Selection Sort.\n";
}

// mengurutkan antrian berdasarkan nilai terbesar dengan Insertion Sort
void urutkanInsertionSort() {
    if (tail <= 1) {
        cout << "Data belum cukup untuk diurutkan.\n";
        return;
    }

    for (int i = head + 1; i < tail; i++) {
        Mahasiswa key = antrian[i];
        int j = i - 1;
        
        // geser data yang lebih kecil ke kanan buat ngasih ruang
        while (j >= head && antrian[j].rataRata < key.rataRata) {
            antrian[j + 1] = antrian[j];
            j = j - 1;
        }
        antrian[j + 1] = key; // sisipkan datanya di posisi yang pas
    }
    cout << "Berhasil diurutkan dengan Insertion Sort.\n";
}

// mereset antrian jadi kosong lagi
void bersihkan() {
	tail = 0; 
	cout << "Antrian sudah dibersihkan.\n";
}

int main(){
	int pilihan;
	
	do {
		cout << "\nMenu Antrian\n";
		cout << "1. Tambah Antrian (Enqueue)\n";
		cout << "2. Proses Antrian (Dequeue)\n";
		cout << "3. Tampilkan Antrian\n";
		cout << "4. Urutkan Data\n";
		cout << "5. Bersihkan Antrian\n";
		cout << "6. Keluar\n";
		cout << "Pilih (1-6): ";
		cin >> pilihan;
		
		switch(pilihan){
			case 1: 
                enqueue(); 
                break;
			case 2: 
                dequeue(); 
                break;
			case 3: 
                tampilkan(); 
                break;
			case 4: {
				int pilihSort;
				cout << "\nPilih metode sorting:\n";
				cout << "1. Bubble Sort\n";
				cout << "2. Selection Sort\n";
				cout << "3. Insertion Sort\n";
				cout << "Pilih (1-3): ";
				cin >> pilihSort;
				
				if (pilihSort == 1) urutkanBubbleSort();
				else if (pilihSort == 2) urutkanSelectionSort();
				else if (pilihSort == 3) urutkanInsertionSort();
				else cout << "Pilihan salah.\n";
				break;
			}
			case 5: 
                bersihkan(); 
                break;
			case 6: 
                cout << "Program selesai.\n"; 
                break;
			default: 
                cout << "Pilihan tidak ada.\n";
		}
	} while(pilihan != 6);

	return 0;	
}
