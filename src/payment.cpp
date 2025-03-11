
#include "payment.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "data.hpp"
#include "menu.hpp"

using namespace std;

const string SPP_DATA_PATH = "../data/pembayaran_spp.txt";

void pay_tuition_fee() {
    PembayaranSPP spp(0, 0, 0, "0");

    cout << "Masukkan id siswa: ";
    cin >> spp.id_siswa;
    cout << "Masukkan nominal: ";
    cin >> spp.nominal;

    ofstream outFile;
    outFile.open(SPP_DATA_PATH, ios::app);
    if (outFile.is_open()) {
        cout << "Pembayaran sebesar Rp." << spp.nominal << " untuk " << spp.id_siswa << " telah diproses." << endl;
        outFile << spp.id_tagihan << " " << spp.id_siswa << " " << fixed << setprecision(2) << spp.nominal << endl;
        pause_input();
        outFile.close();
    } else {
        cout << RED << "Gagal menyimpan data." << endl;
    }
}

void show_payment_list() {
    ifstream inFile(SPP_DATA_PATH);
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
        cout << RED << "Gagal membaca data" << endl;
        pause_input();
    }
}

void search_payment_status() {
    PembayaranSPP spp(0, 0, 0, "0");
    Siswa siswa(0, "", 0, 0, false, "", "", "");
    cout << "Masukkan id siswa: ";
    cin >> spp.id_siswa;

    ifstream inFile(SPP_DATA_PATH);
    string line;
    bool found = false;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            istringstream iss(line);
            int id_siswa;
            double amount;
            iss >> id_siswa >> amount;
            if (id_siswa == spp.id_siswa) {
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
        cout << RED << "Gagal membaca data." << endl;
        pause_input();
    }
}