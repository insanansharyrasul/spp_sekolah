#include <iostream>
using namespace std;

#include "menu.hpp"

void show_menu_admin() {
    clrscr();
    cout << YELLOW << "███████╗██████╗ ██████╗  ██████╗███████╗███╗   ██╗████████╗███████╗██████╗ " << endl;
    cout << YELLOW << "██╔════ ██╔══██╗██╔══██╗██╔════╝██╔════╝████╗  ██║╚══██╔══╝██╔════╝██╔══██╗" << endl;
    cout << YELLOW << "███████ ██████╔╝██████╔╝██║     █████╗  ██╔██╗ ██║   ██║   █████╗  ██████╔╝" << endl;
    cout << YELLOW << "╚════██ ██╔═══╝ ██╔═══╝ ██║     ██╔══╝  ██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗" << endl;
    cout << YELLOW << "███████ ██║     ██║     ╚██████╗███████╗██║ ╚████║   ██║   ███████╗██║  ██║" << endl;
    cout << YELLOW << "╚══════╝╚═╝     ╚═╝     ╚═════╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝ " << endl;
    cout << CYAN << "Halo Admin, apakah ada yang ingin anda lakukan?" << endl;
    cout << CYAN << "1. Lihat Seluruh Pembayaran" << endl;
    cout << CYAN << "2. Daftarkan Siswa Baru" << endl;
    cout << CYAN << "3. Atur Jadwal Pembayaran" << endl;
    cout << CYAN << "4. Jawab Pertanyaan Siswa" << endl;
    cout << CYAN << "5. Exit" << endl;
    cout << CYAN << "Masukkan pilihanmu: ";
}

bool handle_admin_choice(int choice) {
    switch (choice) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
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