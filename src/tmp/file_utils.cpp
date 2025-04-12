#include <color.hpp>
#include <file_path.hpp>
#include <file_utils.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <menu.hpp>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<size_t, string> load_certificate_map() {
    unordered_map<size_t, string> certificate_data;
    ifstream inFile(CERTIFICATE_PATH);
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ',');
            size_t signature = stoull(token);
            getline(ss, token, ',');
            string encrypted_data = token;

            certificate_data[signature] = encrypted_data;
        }
        inFile.close();
    } else {
        cout << RED << "Gagal membaca sertifikat." << endl;
    }
    return certificate_data;
}

unordered_map<string, PembayaranSPP> load_spp_map() {
    unordered_map<string, PembayaranSPP> payments;
    ifstream inFile(SPP_DATA_PATH);

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            PembayaranSPP spp;
            string token;

            getline(ss, token, ',');
            spp.id_tagihan = token;
            getline(ss, token, ',');
            spp.id_student = stoi(token);
            getline(ss, token, ',');
            spp.nominal = stod(token);
            getline(ss, token, ',');
            spp.timestamp = stol(token);

            payments[spp.id_tagihan] = spp;
        }
        inFile.close();
    } else {
        cout << RED << "Gagal membaca data." << endl;
    }

    return payments;
};

unordered_map<int, Student> load_students_map() {
    Student student;
    unordered_map<int, Student> students;
    ifstream siswaFile(STUDENT_DATA_PATH);
    string line;

    if (siswaFile.is_open()) {
        while (getline(siswaFile, line)) {
            stringstream ss(line);
            string token;
            string name;

            getline(ss, token, ',');
            student.id_student = stoi(token);
            getline(ss, token, ',');
            student.year_registered = stoi(token);
            getline(ss, token, ',');
            student.id_class = stoi(token);
            getline(ss, token, ',');
            student.name = token;

            students[student.id_student] = student;
        }
    } else {
        cout << RED << "Gagal membaca data siswa." << endl;
        pause_input();
        return students;
    }

    siswaFile.close();
    return students;
}

void append_spp(PembayaranSPP spp) {
    time_t current_time = time(0);
    ofstream outFile(SPP_DATA_PATH, ios::app);
    if (outFile.is_open()) {
        outFile << fixed << setprecision(2)
                << spp.id_tagihan << ","
                << spp.id_student << ","
                << spp.nominal << ","
                << current_time << endl;
        outFile.close();
    } else {
        cout << RED << "Gagal menyimpan data." << endl;
    }
}

void append_student(Student student) {
    ofstream outFile(STUDENT_DATA_PATH, ios::app);
    if (outFile.is_open()) {
        outFile << student.id_student << ","
                << student.year_registered << ","
                << student.id_class << ","
                << student.name << endl;
        outFile.close();
    } else {
        cout << RED << "Gagal menyimpan data." << endl;
    }
}

void append_certificate(size_t hash_key, string data) {
    ofstream outFile(CERTIFICATE_PATH, ios::app);
    if (outFile.is_open()) {
        outFile << hash_key
                << "," << data << endl;
        outFile.close();
    } else {
        cout << RED << "Gagal menyimpan sertifikat." << endl;
    }
}

unordered_map<string, PembayaranSPP> SPP_DATA = load_spp_map();
unordered_map<size_t, string> CERTIFICATE_DATA = load_certificate_map();
unordered_map<int, Student> STUDENT_DATA = load_students_map();