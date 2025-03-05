#include "menu.h"
#include "payment.h"

#include <iostream>

using namespace std;

void show_menu() {
    cout << "=== PEMBAYARAN SPP ===" << endl;
    cout << "1. Bayar SPP" << endl;
    cout << "2. Cek Pembayaran" << endl;
    cout << "3. Exit" << endl;
    cout << "Masukkan pilihanmu: ";
}

void handle_user_choice(int choice) {
    switch (choice) {
        case 1:
            pay_tuition_fee();
            break;
        case 2:
            check_payment_status();
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Pilihan tidak ada, silahkan ulang lagi." << endl;
            break;
    }
}