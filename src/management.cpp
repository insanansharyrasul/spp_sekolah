#include <data.hpp>
#include <fstream>
#include <iostream>
#include <management.hpp>
#include <menu.hpp>
#include <string>
#include <sstream>
#include <file_path.hpp>
#include <time_set.hpp>

using namespace std;


int hash_id(int id) {
    time_init();
    int current_year_hash = ((timeinfo->tm_year + 1900) % 100) * 1000;
    return SEKOLAH_ID + current_year_hash + id;
}

void new_student() {
    time_init();
    ifstream inFile(STUDENT_DATA_PATH);
    int highest_id = 0;
    bool student_exists = false;
    string line;
    string new_name;
    
    cout << "Masukkan Nama Siswa: ";
    cin.ignore();
    getline(cin, new_name);

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            stringstream ss(line);
            string token;

            getline(ss, token, ',');
            int id = stoi(token);
            getline(ss, token, ',');
            int year = stoi(token);
            getline(ss, token, ',');     
            int class_id = stoi(token);
            getline(ss, token, ',');
            string name = token;

            if (id > highest_id) {
                highest_id = id;
            }
            
            if (name == new_name) {
                student_exists = true;
                cout << RED << "Siswa dengan nama yang sama sudah terdaftar (ID: " << id << ")." << endl;
                pause_input();
                inFile.close();
                return;
            }
        }
        inFile.close();
    }
    
    int current_year = timeinfo->tm_year + 1900;

    int new_id = hash_id(highest_id % 10 + 1);
    
    Student student(new_id, new_name, current_year, 0);
    
    cout << "Masukkan ID Kelas: ";
    cin >> student.id_kelas;

    ofstream outFile(STUDENT_DATA_PATH, ios::app);
    if (outFile.is_open()) {
        outFile << student.id_student << "," << student.year_registered << "," << student.id_kelas << "," << student.nama << endl;
        outFile.close();
        cout << GREEN << "Data Siswa berhasil disimpan dengan ID: " << new_id << endl;
        pause_input();
    } else {
        cout << RED << "Gagal menyimpan data." << endl;
        pause_input();
    }
}