#include <algorithm>
#include <data.hpp>
#include <file_path.hpp>
#include <file_utils.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <menu.hpp>
#include <sorting.hpp>
#include <sstream>
#include <vector>
using namespace std;

void display_sorted_payment() {
    vector<PembayaranSPP> payments;
    payments.reserve(SPP_DATA.size());
    for (const auto& pair : SPP_DATA) {
        payments.push_back(pair.second);
    }

    sort(payments.begin(), payments.end(), [](const PembayaranSPP& a, const PembayaranSPP& b) {
        return a.timestamp > b.timestamp;
    });

    string sort_method = "Tanggal (Terbaru)";
    bool continue_sorting = true;

    while (continue_sorting) {
        clrscr();
        cout << "DATA PEMBAYARAN - Diurutkan berdasarkan: " << sort_method << endl
             << endl;

        cout << "+" << string(10, '-') << "+" << string(10, '-') << "+"
             << string(15, '-') << "+" << string(30, '-') << "+" << endl;

        cout << "│" << setw(10) << left << " ID SPP" << "│"
             << setw(10) << left << " Siswa ID" << "│"
             << setw(15) << left << " Nominal (Rp)" << "│"
             << setw(30) << left << " Tanggal Pembayaran" << "│" << endl;

        cout << "+" << string(10, '-') << "+" << string(10, '-') << "+"
             << string(15, '-') << "+" << string(30, '-') << "+" << endl;

        for (const PembayaranSPP& payment : payments) {
            std::string date_str = ctime(&payment.timestamp);
            if (!date_str.empty() && date_str.back() == '\n') {
                date_str.pop_back();
            }

            cout << "│ " << setw(9) << left << payment.id_tagihan << "│"
                 << " " << setw(9) << left << payment.id_student << "│"
                 << setw(14) << right << fixed << setprecision(2) << payment.nominal << " │"
                 << " " << setw(29) << left << date_str << "│" << endl;
        }

        cout << "+" << string(10, '-') << "+" << string(10, '-') << "+"
             << string(15, '-') << "+" << string(30, '-') << "+" << endl;

        cout << "\n=== OPSI PENGURUTAN ===" << endl;
        cout << "1. Berdasarkan ID SPP" << endl;
        cout << "2. Berdasarkan ID Siswa" << endl;
        cout << "3. Berdasarkan Tanggal Pembayaran (Terbaru)" << endl;
        cout << "4. Berdasarkan Tanggal Pembayaran (Terlama)" << endl;
        cout << "5. Berdasarkan Nominal (Terbesar)" << endl;
        cout << "6. Berdasarkan Nominal (Terkecil)" << endl;
        cout << "7. Kembali ke Menu Utama" << endl;
        cout << "\nPilihan Anda: ";

        int option;
        cin >> option;

        switch (option) {
            case 1:
                sort(payments.begin(), payments.end(), [](const PembayaranSPP& a, const PembayaranSPP& b) {
                    return a.id_tagihan < b.id_tagihan;
                });
                sort_method = "ID SPP";
                break;
            case 2:
                sort(payments.begin(), payments.end(), [](const PembayaranSPP& a, const PembayaranSPP& b) {
                    return a.id_student < b.id_student;
                });
                sort_method = "ID Siswa";
                break;
            case 3:
                sort(payments.begin(), payments.end(), [](const PembayaranSPP& a, const PembayaranSPP& b) {
                    return a.timestamp > b.timestamp;  // Descending (newest first)
                });
                sort_method = "Tanggal (Terbaru)";
                break;
            case 4:
                sort(payments.begin(), payments.end(), [](const PembayaranSPP& a, const PembayaranSPP& b) {
                    return a.timestamp < b.timestamp;  // Ascending (oldest first)
                });
                sort_method = "Tanggal (Terlama)";
                break;
            case 5:
                sort(payments.begin(), payments.end(), [](const PembayaranSPP& a, const PembayaranSPP& b) {
                    return a.nominal > b.nominal;  // Descending (largest first)
                });
                sort_method = "Nominal (Terbesar)";
                break;
            case 6:
                sort(payments.begin(), payments.end(), [](const PembayaranSPP& a, const PembayaranSPP& b) {
                    return a.nominal < b.nominal;  // Ascending (smallest first)
                });
                sort_method = "Nominal (Terkecil)";
                break;
            case 7:
                continue_sorting = false;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                pause_input();
                break;
        }
    }
}