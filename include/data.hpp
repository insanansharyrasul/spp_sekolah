#pragma once
#include <ctime>
#include <string>

struct Student {
    int id_student;
    std::string nama;
    int year_registered;
    int id_kelas;

    Student(int id_student = 0, const std::string& name = "", int year = 0, int class_id = 0) {
        this->id_student = id_student;
        this->nama = name;
        this->year_registered = year;
        this->id_kelas = class_id;
    }
};

struct PembayaranSPP {
    int id_student;
    int id_tagihan;
    double nominal;
    time_t timestamp;

    PembayaranSPP(int id_student = 0, int id_tagihan = 0, double nominal = 0, time_t timestamp = time(0)) {
        this->id_tagihan = id_tagihan;
        this->id_student = id_student;
        this->nominal = nominal;
        this->timestamp = timestamp;
    }
};