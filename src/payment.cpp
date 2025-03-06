
#include "payment.hpp"
#include "menu.hpp"
#include "data.hpp"

#include <limits>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>


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
        pause_input();
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
        cout << "==========================" << endl;
        pause_input();
        inFile.close();
    } else {
        cout << "Gagal membaca data" << endl;
        pause_input();
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
                pause_input();
                inFile.close();
                break;
            }
        }

        if (!found) {
            inFile.close();
            cout << "Pembayaran untuk " << siswa.nama << ": Belum Dibayar" << endl;
            pause_input();
        }
    } else {
        cout << "Gagal membaca data." << endl;
        pause_input();
    }
}