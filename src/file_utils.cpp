#include <file_path.hpp>
#include <file_utils.hpp>
#include <fstream>
#include <vector>
#include <sstream>
#include <menu.hpp>
#include <iostream>
#include <unordered_map>
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

unordered_map<int, PembayaranSPP> load_spp_map() {
    unordered_map<int, PembayaranSPP> payments;
    ifstream inFile(SPP_DATA_PATH);

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            PembayaranSPP spp;
            string token;

            getline(ss, token, ',');
            spp.id_tagihan = stoi(token);
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

vector<Student> load_students_vector() {
    Student student;
    vector<Student> students;
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
            student.id_kelas = stoi(token);
            getline(ss, token, ',');
            student.nama = token;

            students.push_back(student);
        }
    } else {
        cout << RED << "Gagal membaca data siswa." << endl;
        pause_input();
        return students;
    }

    siswaFile.close();
    return students;
}
