#include "sorting.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <file_path.hpp>
#include <iomanip>
using namespace std;

vector<pair<int, string>> load_students() {
    vector<pair<int, string>> students;
    ifstream siswaFile(SISWA_DATA_PATH);
    string line;
    if (siswaFile.is_open()) {
        while (getline(siswaFile, line)) {
            istringstream iss(line);
            int id;
            string name;
            if (iss >> id) {
                iss >> ws;
                getline(iss, name);
                students.push_back({id, name});
            }
        }
        siswaFile.close();
    } else {
        cout << "Gagal membuka file siswa." << endl;
    }
    return students;
}

void save_students(const vector<pair<int, string>>& students) {
    ofstream siswaFile(SISWA_DATA_PATH, ios::trunc);
    if (siswaFile.is_open()) {
        for (const auto& student : students) {
            siswaFile << student.first << " " << student.second << endl;
        }
        siswaFile.close();
    } else {
        cout << "Gagal menulis ke file siswa." << endl;
    }
}

void sort_students_by_name() {
    auto students = load_students();
    sort(students.begin(), students.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.second < b.second;
    });
    save_students(students);
    cout << "Siswa berhasil diurutkan berdasarkan nama." << endl;
}

void sort_students_by_id() {
    auto students = load_students();
    sort(students.begin(), students.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first < b.first;
    });
    save_students(students);
    cout << "Siswa berhasil diurutkan berdasarkan ID." << endl;
}

void print_students() {
    vector<pair<int, string>> students = load_students();
    cout << "ID Siswa\tNama Siswa" << endl;
    for (const auto& student : students) {
        cout << setw(8) << left << student.first  << setw(12) << left << student.second << endl;
    }
}