#include "payment.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "data.hpp"
#include "menu.hpp"
#include <file_path.hpp>

using namespace std;

const time_t current_time = time(0);

void pay_tuition_fee(int id_siswa) {
    // The parameter is:
    // id_siswa , id_tagihan , nominal , timestamp
    PembayaranSPP spp(id_siswa, 0, 0, current_time);

    ifstream inFile(SPP_DATA_PATH);
    string line;
    int last_id_tagihan = 0;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            istringstream iss(line);
            int id_tagihan;
            iss >> id_tagihan;
            last_id_tagihan = id_tagihan;
        }
        inFile.close();
    }

    spp.id_tagihan = last_id_tagihan + 1;

    cout << "Masukkan nominal: ";
    cin >> spp.nominal;

    ofstream outFile;
    outFile.open(SPP_DATA_PATH, ios::app);
    if (outFile.is_open()) {
        cout << "Pembayaran sebesar Rp." << spp.nominal << " untuk " << spp.id_siswa << " telah diproses." << endl;
        cout << "Pembayaran dilakukan pada: " << ctime(&current_time) << endl;
        outFile << spp.id_tagihan << " " << spp.id_siswa << " " << fixed << setprecision(2) << spp.nominal << " " << current_time << endl;
        pause_input();
        outFile.close();
    } else {
        cout << RED << "Gagal menyimpan data." << endl;
    }
}

void show_payment_list() {
    ifstream inFile(SPP_DATA_PATH);
    string line;

    if (inFile.is_open()) {
        cout << "=== STATUS PEMBAYARAN ===" << endl;
        while (getline(inFile, line)) {
            cout << fixed << setprecision(2) << line << endl;
        }
        cout << "==========================" << endl;
        pause_input();
        inFile.close();
    } else {
        cout << RED << "Gagal membaca data" << endl;
        pause_input();
    }
}

void search_payment_status(int id_siswa) {
    PembayaranSPP spp(id_siswa, 0, 0, current_time);
    string student_name = "UNKNOWN";

    ifstream inFile(SPP_DATA_PATH);
    ifstream siswaFile(SISWA_DATA_PATH);
    string line;

    if (siswaFile.is_open()) {
        while (getline(siswaFile, line)) {
            istringstream iss(line);
            int current_id;
            string name;

            iss >> current_id;

            if (current_id == id_siswa) {
                iss >> ws;

                getline(iss, name);
                student_name = name;
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
            istringstream iss(line);
            int id_tagihan;
            int id_siswa;
            double amount;
            time_t timestamp;
            iss >> id_tagihan >> id_siswa >> amount >> timestamp;
            if (id_siswa == spp.id_siswa) {
                cout << "Pembayaran untuk " << student_name << ": Dibayar" << endl;
                cout << "Pada tanggal: " << ctime(&timestamp) << endl;
                // cout << line << endl;
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