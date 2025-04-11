#include <data.hpp>
#include <fstream>
#include <iostream>
#include <management.hpp>
#include <menu.hpp>
#include <string>
#include <sstream>
#include <file_path.hpp>
#include <time_set.hpp>
#include <file_utils.hpp>

using namespace std;


int hash_id(int id) {
    time_init();
    int current_year_hash = ((timeinfo->tm_year + 1900) % 100) * 1000;
    return SEKOLAH_ID + current_year_hash + id;
}

void new_student() {
    time_init();
    int highest_id = 0;
    for (const auto& pair : STUDENT_DATA) {
        if (pair.first > highest_id) {
            highest_id = pair.first;
        }
    }

    bool student_exists = false;
    int current_year = timeinfo->tm_year + 1900;
    int new_id = hash_id(highest_id % 10 + 1);
    string new_name;
    
    cout << "Masukkan Nama Siswa: ";
    cin.ignore();
    getline(cin, new_name);
    
    Student student(new_id, new_name, current_year, 0);
    
    cout << "Masukkan ID Kelas: ";
    cin >> student.id_class;

    STUDENT_DATA[new_id] = student;
    append_student(student);
    cout << GREEN << "Data Siswa berhasil disimpan dengan ID: " << new_id << endl;
}