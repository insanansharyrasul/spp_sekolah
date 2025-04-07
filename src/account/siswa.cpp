#include <iostream>
using namespace std;

#include <limits>
#include <payment.hpp>

#include "menu.hpp"
#include "siswa.hpp"

int verify_siswa() {
    clrscr();
    cout << "Silahkan masukkan ID Anda: ";
    int id;
    cin >> id;

    if (id == 123) {
        cout << "Siswa terverifikasi." << endl;
        pause_input();
        return id;
    } else {
        cout << "Siswa tidak terverifikasi." << endl;
        pause_input();
        return -1;
    }
}

void show_menu_siswa() {
    clrscr();
    cout << YELLOW << "███████╗██████╗ ██████╗  ██████╗███████╗███╗   ██╗████████╗███████╗██████╗ " << endl;
    cout << YELLOW << "██╔════ ██╔══██╗██╔══██╗██╔════╝██╔════╝████╗  ██║╚══██╔══╝██╔════╝██╔══██╗" << endl;
    cout << YELLOW << "███████ ██████╔╝██████╔╝██║     █████╗  ██╔██╗ ██║   ██║   █████╗  ██████╔╝" << endl;
    cout << YELLOW << "╚════██ ██╔═══╝ ██╔═══╝ ██║     ██╔══╝  ██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗" << endl;
    cout << YELLOW << "███████ ██║     ██║     ╚██████╗███████╗██║ ╚████║   ██║   ███████╗██║  ██║" << endl;
    cout << YELLOW << "╚══════╝╚═╝     ╚═╝     ╚═════╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝ " << endl;
    cout << CYAN << "Halo ";
    cout << CYAN << "XXX ";
    cout << CYAN << "Apakah ada yang ingin anda lakukan?" << endl;
    cout << CYAN << "1. Lihat detail SPP saya" << endl;
    cout << CYAN << "2. Bayar SPP" << endl;
    cout << CYAN << "3. Bertanya kepada admin" << endl;
    cout << CYAN << "4. Lihat Sertifikat" << endl;
    cout << CYAN << "5. Kembali ke menu utama" << endl;
    cout << CYAN << "6. Exit" << endl;
    cout << CYAN << "Masukkan pilihanmu: ";
}

VerificationStatus handle_siswa_choice(int choice, int id_siswa) {
    switch (choice) {
        case 1:
            search_payment_status(id_siswa);
            break;
        case 2:
            // show_payment_list();
            pay_tuition_fee(id_siswa);
            break;
        case 3:
            // search_payment_status();
            break;
        case 4:
            // search_payment_status();
            break;
        case 5:
            cout << "Going back to main menu..." << endl;
            pause_input();
            return BACK;
            break;
        case 6:
            cout << "Exiting..." << endl;
            exit(0);
            break;
        default:
            cout << "Pilihan tidak ada, silahkan ulang lagi." << endl;
            pause_input();
            break;
    }
    return VERIFIED;
}