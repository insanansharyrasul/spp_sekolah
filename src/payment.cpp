#include <file_path.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <time_set.hpp>
#include <data.hpp>
#include <menu.hpp>
#include <vector>
#include <certificate.hpp>
#include <file_utils.hpp>


using namespace std;

void pay_tuition_fee(int id_student) {
    time_init();
    PembayaranSPP spp;
    spp.id_student = id_student;

    int last_id_tagihan = 0;
    for (PembayaranSPP i : SPP_DATA) {
        if (i.id_tagihan > last_id_tagihan) {
            last_id_tagihan = i.id_tagihan;
        }
    }

    spp.id_tagihan = last_id_tagihan + 1;

    cout << "Masukkan nominal: ";
    cin >> spp.nominal;

    ofstream outFile;
    outFile.open(SPP_DATA_PATH, ios::app);

    char date_buffer[30];
    strftime(date_buffer, sizeof(date_buffer), " %d-%m-%Y %H:%M:%S",
             localtime_r(&current_time, timeinfo));

    if (outFile.is_open()) {
        cout << "Pembayaran sebesar Rp." << spp.nominal << " untuk " << spp.id_student << " telah diproses." << endl;
        cout << "Pembayaran dilakukan pada: " << date_buffer << endl;
        outFile << spp.id_tagihan << "," << spp.id_student << "," << fixed << setprecision(2) << spp.nominal << "," << current_time << endl;
        SPP_DATA.push_back(spp);
        pause_input();
        outFile.close();
    } else {
        cout << RED << "Gagal menyimpan data." << endl;
    }
}

void show_payment_list() {
    time_init();

        clrscr();

        cout << "│" << setw(10) << left << " ID SPP" << "│"
             << setw(10) << left << " Siswa ID" << "│"
             << setw(15) << left << " Nominal (Rp)" << "│"
             << setw(30) << left << " Tanggal Pembayaran" << "│" << endl;

        cout << "│" << setw(10) << left << " " << "│"
             << setw(10) << left << " " << "│"
             << setw(15) << right << " " << "│"
             << setw(30) << left << " " << "│" << endl;

        for (const PembayaranSPP& i : SPP_DATA) {
            std::string date_str = ctime(&i.timestamp);
            if (!date_str.empty() && date_str.back() == '\n') {
                date_str.pop_back();
            }

            cout << "│" << " " << setw(9) << left << i.id_tagihan << "│"
                 << " " << setw(9) << left << i.id_student << "│"
                 << setw(14) << right << fixed << setprecision(2) << i.nominal << " │"
                 << " " << setw(29) << left << date_str << "│" << endl;
        }

        pause_input();
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
