#include "menu.hpp"

#include <iostream>

#include "payment.hpp"

using namespace std;

void show_menu() {
    cout << "=== PEMBAYARAN SPP ===" << endl;
    cout << "1. Bayar SPP" << endl;
    cout << "2. Cek Pembayaran" << endl;
    cout << "3. Cari Pembayaran" << endl;
    cout << "4. Exit" << endl;
    cout << "Masukkan pilihanmu: ";
}

bool handle_user_choice(int choice) {
    switch (choice) {
        case 1:
            pay_tuition_fee();
            break;
        case 2:
            show_payment_list();
            break;
        case 3:
            search_payment_status();
            break;
        case 4:
            cout << "Exiting..." << endl;
            return false;
            break;
        default:
            cout << "Pilihan tidak ada, silahkan ulang lagi." << endl;
            return true;
            break;
    }
    return true;
}