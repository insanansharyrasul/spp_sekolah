#include "payment.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "siswa.h"

using namespace std;

const string DATA_PATH = "../data/payment.txt";

void pay_tuition_fee() {
    Siswa siswa;

    cout << "Masukkan nama siswa: ";
    cin >> siswa.nama;
    cout << "Masukkan jumlah: ";
    cin >> siswa.spp;

    ofstream outFile;
    outFile.open(DATA_PATH, ios::app);
    if (outFile.is_open()) {
        cout << "Pembayaran dari Rp." << siswa.spp << " untuk " << siswa.nama << " telah diproses." << endl;
        outFile << siswa.nama << " " << fixed << setprecision(2) << siswa.spp << endl;
        outFile.close();
    } else {
        cout << "Gagal menyimpan data." << endl;
    }
}

void show_payment_list() {
    ifstream inFile(DATA_PATH);
    string line;

    if (inFile.is_open()) {
        cout << "=== STATUS PEMBAYARAN ===" << endl;
        while (getline(inFile, line)) {
            cout << fixed << setprecision(2) << line << endl;
        }
        inFile.close();
    } else {
        cout << "Gagal membaca data" << endl;
    }
}

void search_payment_status() {
    Siswa siswa;
    cout << "Masukkan nama siswa: ";
    cin >> siswa.nama;

    ifstream inFile(DATA_PATH);
    string line;
    bool found = false;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            istringstream iss(line);
            string name;
            double amount;
            iss >> name >> amount;
            if (name == siswa.nama) {
                cout << "Pembayaran untuk " << siswa.nama << ": Dibayar" << endl;
                cout << line << endl;
                found = true;
                inFile.close();
                break;
            }
        }

        if (!found) {
            inFile.close();
            cout << "Pembayaran untuk " << siswa.nama << ": Belum Dibayar" << endl;
        }
    } else {
        cout << "Gagal membaca data." << endl;
    }
}