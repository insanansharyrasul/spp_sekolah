#include <certificate.hpp>
#include <data.hpp>
#include <file_path.hpp>
#include <file_utils.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <menu.hpp>
#include <sstream>
#include <string>
#include <time_set.hpp>
#include <vector>

using namespace std;

void pay_tuition_fee(int id_student) {
    clrscr();
    time_init();
    PembayaranSPP spp;
    spp.id_student = id_student;

    char date_part[7];
    strftime(date_part, sizeof(date_part), "%Y%m", timeinfo);
    spp.id_tagihan = std::string(date_part) + "-" + std::to_string(id_student);
    
    int suffix = 1;
    string base_id = spp.id_tagihan;
    while (SPP_DATA.find(spp.id_tagihan) != SPP_DATA.end()) {
        spp.id_tagihan = base_id + "-" + std::to_string(suffix++);
    }

    cout << "Masukkan nominal: ";
    cin >> spp.nominal;

    append_spp(spp);
    SPP_DATA[spp.id_tagihan] = spp;
    cout << "Pembayaran sebesar Rp." << spp.nominal << " untuk " << spp.id_student << " telah diproses." << endl;
    cout << "Pembayaran dilakukan pada: " << ctime(&current_time) << endl;
    pause_input();
}

void search_payment_status(int id_student) {
    clrscr();
    int year, month, day;
    PembayaranSPP spp;
    Student student;

    cout << "Masukkan tahun tagihan (YYYY): ";
    cin >> year;
    cout << endl;
    cout << "Masukkan bulan tagihan (1-12): ";
    cin >> month;
    cout << endl;
    cout << "Masukkan tanggal tagihan(1-31): ";
    cin >> day;

    string id_tagihan = to_string(year) +
                        (month < 10 ? "0" : "") +
                        to_string(month) +
                        to_string(id_student);

    auto it_spp = SPP_DATA.find(id_tagihan);
    if (it_spp != SPP_DATA.end()) {
        spp = it_spp->second;
    } else {
        cout << RED << "Pembayaran tidak ditemukan." << endl;
        pause_input();
        return;
    }

    auto it_student = STUDENT_DATA.find(id_student);
    if (it_student != STUDENT_DATA.end()) {
        student = it_student->second;
    } else {
        cout << RED << "Siswa tidak ditemukan." << endl;
        pause_input();
        return;
    }

    clrscr();
    cout << "Pembayaran untuk siswa ID " << id_student << endl;
    cout << "----------------------------------------" << endl;
    cout << "Nama Siswa:" << student.name << endl;
    cout << "ID Tagihan: " << spp.id_tagihan << endl;
    cout << "Nominal: Rp." << spp.nominal << endl;
    cout << "Tanggal: " << ctime(&current_time) << endl;
    cout << "----------------------------------------" << endl;
    pause_input();
}

void set_tuition() {
    clrscr();
    cout << "Masukkan nominal SPP: ";
    int nominal;
    cin >> nominal;

    ofstream file(SPP_DATA_PATH);
    if (file.is_open()) {
        file << nominal;
        file.close();
        cout << "Nominal SPP berhasil disimpan." << endl;
    } else {
        cout << RED << "Gagal menyimpan data SPP." << endl;
    }
    pause_input();
}