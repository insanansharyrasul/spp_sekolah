#include <data.hpp>
#include <fstream>
#include <iostream>
#include <management.hpp>
#include <menu.hpp>
#include <string>
#include <sstream>
#include <file_path.hpp>

using namespace std;

const time_t current_time = time(0);
struct tm* timeinfo = localtime(&current_time);
int current_year_hash = ((timeinfo->tm_year + 1900) % 100) * 1000;
const int SEKOLAH_ID = 91100000;  // 5 zeros

int hash_id(int id) {
    return SEKOLAH_ID + current_year_hash + id;
}

void new_siswa() {
    ifstream inFile(SISWA_DATA_PATH);
    int highest_id = 0;
    bool student_exists = false;
    string line;
    string new_name;
    
    cout << "Masukkan Nama Siswa: ";
    cin.ignore();
    getline(cin, new_name);

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            istringstream iss(line);
            int id;
            int year, class_id;
            string name;
            
            iss >> id >> year >> class_id;
            
            if (id > highest_id) {
                highest_id = id;
            }
            
            iss >> ws;
            getline(iss, name);
            
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
    
    struct tm* timeinfo = localtime(&current_time);
    int current_year = timeinfo->tm_year + 1900;

    int new_id = hash_id(highest_id % 10 + 1);
    
    // Parameter siswa:
    // id_siswa, nama, tahun_masuk, id_kelas
    Siswa siswa(new_id, new_name, current_year, 0);
    
    cout << "Masukkan ID Kelas: ";
    cin >> siswa.id_kelas;

    ofstream outFile(SISWA_DATA_PATH, ios::app);
    if (outFile.is_open()) {
        outFile << siswa.id_siswa << " " << siswa.tahun_masuk << " " << siswa.id_kelas << " " << siswa.nama << endl;
        outFile.close();
        cout << GREEN << "Data Siswa berhasil disimpan dengan ID: " << new_id << endl;
        pause_input();
    } else {
        cout << RED << "Gagal menyimpan data." << endl;
        pause_input();
    }
}