#include "menu.hpp"
#include "siswa.hpp"
#include "admin.hpp"

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

void show_account() {
    clrscr();
    cout << YELLOW << "███████╗██████╗ ██████╗  ██████╗███████╗███╗   ██╗████████╗███████╗██████╗ " << endl;
    cout << YELLOW << "██╔════ ██╔══██╗██╔══██╗██╔════╝██╔════╝████╗  ██║╚══██╔══╝██╔════╝██╔══██╗" << endl;
    cout << YELLOW << "███████ ██████╔╝██████╔╝██║     █████╗  ██╔██╗ ██║   ██║   █████╗  ██████╔╝" << endl;
    cout << YELLOW << "╚════██ ██╔═══╝ ██╔═══╝ ██║     ██╔══╝  ██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗" << endl;
    cout << YELLOW << "███████ ██║     ██║     ╚██████╗███████╗██║ ╚████║   ██║   ███████╗██║  ██║" << endl;
    cout << YELLOW << "╚══════╝╚═╝     ╚═╝     ╚═════╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝ " << endl;
    cout << CYAN << "Selamat datang di SPP-Center, sebagai apakah anda ingin mendaftar?" << endl;
    cout << CYAN << "1. Admin" << endl;
    cout << CYAN << "2. Siswa" << endl;
    cout << CYAN << "3. Exit" << endl;
    cout << CYAN << "Masukkan pilihanmu: ";
}