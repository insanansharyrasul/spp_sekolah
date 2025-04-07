#include <iostream>
using namespace std;

#include <payment.hpp>

#include "menu.hpp"
#include <management.hpp>

void show_menu_admin() {
    clrscr();
    cout << YELLOW << "███████╗██████╗ ██████╗  ██████╗███████╗███╗   ██╗████████╗███████╗██████╗ " << endl;
    cout << YELLOW << "██╔════ ██╔══██╗██╔══██╗██╔════╝██╔════╝████╗  ██║╚══██╔══╝██╔════╝██╔══██╗" << endl;
    cout << YELLOW << "███████ ██████╔╝██████╔╝██║     █████╗  ██╔██╗ ██║   ██║   █████╗  ██████╔╝" << endl;
    cout << YELLOW << "╚════██ ██╔═══╝ ██╔═══╝ ██║     ██╔══╝  ██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗" << endl;
    cout << YELLOW << "███████ ██║     ██║     ╚██████╗███████╗██║ ╚████║   ██║   ███████╗██║  ██║" << endl;
    cout << YELLOW << "╚══════╝╚═╝     ╚═╝     ╚═════╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝ " << endl;
    cout << WHITE << "Halo ";
    cout << RED << "Admin ";
    cout << WHITE << "apakah ada yang ingin anda lakukan?" << endl;
    cout << WHITE << "1. Lihat Seluruh Pembayaran" << endl;
    cout << WHITE << "2. Daftarkan Siswa Baru" << endl;
    cout << WHITE << "3. Atur Jadwal Pembayaran" << endl;
    cout << WHITE << "4. Jawab Pertanyaan Siswa" << endl;
    cout << WHITE << "5. Kembali ke menu" << endl;
    cout << WHITE << "6. Exit" << endl;
    cout << WHITE << "Masukkan pilihanmu: ";
}

VerificationStatus handle_admin_choice(int choice) {
    switch (choice) {
        case 1:
            show_payment_list();
            break;
        case 2:
            new_siswa();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            cout << "Kembali ke menu utama..." << endl;
            pause_input();
            clrscr();
            return BACK;
            break;
        case 6:
            cout << "Exiting..." << endl;
            exit(0);
        default:
            cout << "Pilihan tidak ada, silahkan ulang lagi." << endl;
            cin.get();
            break;
    }
    return VERIFIED;
}