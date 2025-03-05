#include "payment.h"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const string DATA_PATH = "../data/payment.txt";

void payTuitionFee() {
    string studentName;
    double amount;

    cout << "Masukkan nama siswa: ";
    cin >> studentName;
    cout << "Masukkan jumlah: ";
    cin >> amount;

    ofstream outFile;
    outFile.open(DATA_PATH, ios::app);
    if (outFile.is_open()) {
        cout << "Pembayaran dari Rp." << amount << " untuk " << studentName << " telah diproses." << endl;
        outFile << studentName << " " << fixed << setprecision(2) << amount << endl;
        outFile.close();
    } else {
        cout << "Gagal menyimpan data." << endl;
    }
}

void checkPaymentStatus() {
    string studentName;

    cout << "Masukkan nama siswa: ";
    cin >> studentName;

    cout << "Pembayaran untuk" << studentName << ": Dibayar" << endl;
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