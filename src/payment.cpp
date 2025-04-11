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

    string date_code = to_string((timeinfo->tm_year + 1900) % 100) +
                       to_string(timeinfo->tm_mon + 1) +
                       to_string(timeinfo->tm_mday);

    string student_suffix = to_string(id_student % 1000);
    spp.id_tagihan = date_code + student_suffix;

    cout << "Masukkan nominal: ";
    cin >> spp.nominal;

    ofstream outFile;
    outFile.open(SPP_DATA_PATH, ios::app);


    if (outFile.is_open()) {
        cout << "Pembayaran sebesar Rp." << spp.nominal << " untuk " << spp.id_student << " telah diproses." << endl;
        cout << "Pembayaran dilakukan pada: " << ctime(&current_time) << endl;
        append_spp(spp);
        SPP_DATA[spp.id_tagihan] = spp;
        pause_input();
        outFile.close();
    } else {
        cout << RED << "Gagal menyimpan data." << endl;
    }
}

void search_payment_status(int id_student) {
    time_init();
    PembayaranSPP spp;
    spp.id_student = id_student;
    string student_name = "UNKNOWN";

    ifstream inFile(SPP_DATA_PATH);
    ifstream siswaFile(STUDENT_DATA_PATH);
    string line;

    if (siswaFile.is_open()) {
        while (getline(siswaFile, line)) {
            stringstream ss(line);
            string token;
            string name;

            getline(ss, token, ',');
            int current_id = stoi(token);

            if (current_id == id_student) {
                getline(ss, token, ',');
                student_name = token;
                break;
            }
        }
        siswaFile.close();
    } else {
        cout << RED << "Gagal membaca data siswa." << endl;
        pause_input();
        return;
    }

    bool found = false;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string token;

            getline(ss, token, ',');
            int id_tagihan = stoi(token);
            getline(ss, token, ',');
            int id_student = stoi(token);
            getline(ss, token, ',');
            double amount = stod(token);
            getline(ss, token, ',');
            time_t timestamp = stol(token);

            char date_buffer[30];
            strftime(date_buffer, sizeof(date_buffer), " %d-%m-%Y %H:%M:%S",
                     localtime_r(&timestamp, timeinfo));

            if (id_student == spp.id_student) {
                cout << "Pembayaran untuk " << student_name << ": Dibayar" << endl;
                cout << "Pada tanggal: " << date_buffer << endl;
                found = true;
                pause_input();
                inFile.close();
                break;
            }
        }

        if (!found) {
            inFile.close();
            cout << "Pembayaran untuk " << student_name << ": Belum Dibayar" << endl;
            pause_input();
        }
    } else {
        cout << RED << "Gagal membaca data." << endl;
        pause_input();
    }
}
