#include <unordered_map>
#include <string>
#include <sstream>
#include <menu.hpp>
#include <iostream>
#include <iomanip>
#include <functional>
#include <fstream>
#include <file_utils.hpp>
#include <file_path.hpp>
#include <data.hpp>
using namespace std;

namespace {
const char XOR_KEY = 'I';
}

size_t generate_signature(const string& data) {
    hash<string> hasher;
    return hasher(data);
}

string xorEncryptDecrypt(string data) {
    string result = data;
    for (char& c : result) {
        c = c ^ XOR_KEY;
    }
    return result;
}

void save_certificate(size_t hash_key, const string& data) {
    ofstream outFile(CERTIFICATE_PATH, ios::app);
    if (outFile.is_open()) {
        outFile << hash_key
                << "," << data << endl;
        outFile.close();
    } else {
        cout << RED << "Gagal menyimpan sertifikat." << endl;
    }
}


void split_by_comma(string line, vector<string>& tokens) {
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }
}

void validate_certificate() {
    vector<string> spp;
    size_t certificate_key;
    cout << "Masukkan kunci sertifikat: ";
    cin >> certificate_key;
    unordered_map<size_t, string> certificate_data = load_certificate_map();

    auto it = certificate_data.find(certificate_key);
    if (it != certificate_data.end()) {
        cout << "Sertifikat ditemukan" << endl;
        cout << "Signature: " << it->first << endl;
        split_by_comma(xorEncryptDecrypt(it->second), spp);
        cout << "ID SPP: " << spp[0] << endl;
        cout << "ID Siswa: " << spp[1] << endl;
        cout << "Nominal: Rp." << fixed << setprecision(2) << stof(spp[2]) << endl;
        time_t date = stol(spp[3]);
        cout << "Tanggal Pembayaran: " << ctime(&date) << endl;
    } else {
        cout << RED << "Sertifikat tidak ditemukan." << endl;
    }
    pause_input();
}

void write_certificate() {
    PembayaranSPP spp;
    unordered_map<int, PembayaranSPP> payments = load_spp_map();
    cout << "Masukkan ID SPP: ";
    cin >> spp.id_tagihan;

    if (payments.find(spp.id_tagihan) == payments.end()) {
        cout << RED << "ID SPP tidak ditemukan." << endl;
        pause_input();
        return;
    }

    cout << "Membuat sertifikat untuk ID SPP: " << spp.id_tagihan << endl;
    cout << "Siswa ID: " << payments[spp.id_tagihan].id_student << endl;
    cout << "Nominal: Rp." << fixed << setprecision(2) << payments[spp.id_tagihan].nominal << endl;
    cout << "Tanggal Pembayaran: " << ctime(&payments[spp.id_tagihan].timestamp) << endl;

    string data = to_string(payments[spp.id_tagihan].id_tagihan) + "," +
                  to_string(payments[spp.id_tagihan].id_student) + "," +
                  to_string(payments[spp.id_tagihan].nominal) + "," +
                  to_string(payments[spp.id_tagihan].timestamp);

    size_t signature = generate_signature(data);
    string encrypted_data = xorEncryptDecrypt(data);

    save_certificate(signature, encrypted_data);
    cout << "Sertifikat berhasil disimpan." << endl;
    cout << "Sertifikat disimpan di: " << CERTIFICATE_PATH << endl;
    cout << "Signature: " << signature << endl;
    pause_input();
}