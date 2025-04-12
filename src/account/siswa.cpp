#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <payment.hpp>
#include <menu.hpp>
#include <siswa.hpp>
#include <file_path.hpp>
#include <certificate.hpp>
#include <file_utils.hpp>
using namespace std;

int verify_siswa(string& student_name) {
    clrscr();
    cout << "Silahkan masukkan ID Anda: ";
    int id;
    cin >> id;

    auto it = STUDENT_DATA.find(id);
    if (it != STUDENT_DATA.end()) {
        student_name = it->second.name;
        cout << "Siswa " << student_name << " berhasil terverifikasi." << endl;
        pause_input();
        return id;
    } else {
        cout << "ID Siswa tidak ditemukan dalam sistem." << endl;
        pause_input();
        return -1;
    }
}

void show_menu_siswa(string student_name) {
    clrscr();
    cout << YELLOW << "███████╗██████╗ ██████╗  ██████╗███████╗███╗   ██╗████████╗███████╗██████╗ " << endl;
    cout << YELLOW << "██╔════ ██╔══██╗██╔══██╗██╔════╝██╔════╝████╗  ██║╚══██╔══╝██╔════╝██╔══██╗" << endl;
    cout << YELLOW << "███████ ██████╔╝██████╔╝██║     █████╗  ██╔██╗ ██║   ██║   █████╗  ██████╔╝" << endl;
    cout << YELLOW << "╚════██ ██╔═══╝ ██╔═══╝ ██║     ██╔══╝  ██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗" << endl;
    cout << YELLOW << "███████ ██║     ██║     ╚██████╗███████╗██║ ╚████║   ██║   ███████╗██║  ██║" << endl;
    cout << YELLOW << "╚══════╝╚═╝     ╚═╝     ╚═════╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝ " << endl;
    cout << WHITE << "Halo ";
    cout << BLUE << student_name;
    cout << WHITE << " Apakah ada yang ingin anda lakukan?" << endl;
    cout << WHITE << "1. Lihat detail SPP saya" << endl;
    cout << WHITE << "2. Bayar SPP" << endl;
    cout << WHITE << "3. Bertanya kepada admin" << endl;
    cout << WHITE << "4. Lihat Sertifikat" << endl;
    cout << WHITE << "5. Kembali ke menu utama" << endl;
    cout << WHITE << "6. Exit" << endl;
    cout << WHITE << "Masukkan pilihanmu: ";
}

VerificationStatus handle_siswa_choice(int choice, int id_student) {
    switch (choice) {
        case 1:
            search_payment_status(id_student);
            break;
        case 2:
            // show_payment_list();
            pay_tuition_fee(id_student);
            break;
        case 3:
            // search_payment_status();
            break;
        case 4:
            validate_certificate();
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