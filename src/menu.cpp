#include "menu.hpp"

#include <iostream>
#include <limits>

#include "payment.hpp"


using namespace std;

void clrscr() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause_input() {
    cout << "Tekan enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void show_menu() {
    clrscr();
    cout << YELLOW << "███████╗██████╗ ██████╗  ██████╗███████╗███╗   ██╗████████╗███████╗██████╗ " << endl;
    cout << YELLOW << "██╔════ ██╔══██╗██╔══██╗██╔════╝██╔════╝████╗  ██║╚══██╔══╝██╔════╝██╔══██╗" << endl;
    cout << YELLOW << "███████ ██████╔╝██████╔╝██║     █████╗  ██╔██╗ ██║   ██║   █████╗  ██████╔╝" << endl;
    cout << YELLOW << "╚════██ ██╔═══╝ ██╔═══╝ ██║     ██╔══╝  ██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗" << endl;
    cout << YELLOW << "███████ ██║     ██║     ╚██████╗███████╗██║ ╚████║   ██║   ███████╗██║  ██║" << endl;
    cout << YELLOW << "╚══════╝╚═╝     ╚═╝     ╚═════╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝ " << endl;
    cout << CYAN << "1. Bayar SPP" << endl;
    cout << CYAN << "2. Cek Pembayaran" << endl;
    cout << CYAN << "3. Cari Pembayaran" << endl;
    cout << CYAN << "4. Exit" << endl;
    cout << CYAN << "Masukkan pilihanmu: ";
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
            cin.get();
            break;
    }
    return true;
}