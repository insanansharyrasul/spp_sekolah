#include "menu.h"

#include <iostream>

#include "payment.h"
using namespace std;

void showMenu() {
    cout << "=== PEMBAYARAN SPP ===" << endl;
    cout << "1. Bayar SPP" << endl;
    cout << "2. Cek Pembayaran" << endl;
    cout << "3. Exit" << endl;
    cout << "Masukkan pilihanmu: ";
}

void handleUserChoice(int choice) {
    switch (choice) {
        case 1:
            payTuitionFee();
            break;
        case 2:
            checkPaymentStatus();
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Pilihan tidak ada, silahkan ulang lagi." << endl;
            break;
    }
}