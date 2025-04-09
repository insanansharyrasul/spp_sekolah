#pragma once
#include <ctime>
#include <string>

struct Siswa {
    int id_siswa;
    std::string nama;
    int tahun_masuk;
    int id_kelas;

    Siswa(int id_siswa = 0, const std::string& name = "", int year = 0, int class_id = 0) {
        this->id_siswa = id_siswa;
        this->nama = name;
        this->tahun_masuk = year;
        this->id_kelas = class_id;
    }
};

struct PembayaranSPP {
    int id_siswa;
    int id_tagihan;
    double nominal;
    time_t timestamp;

    PembayaranSPP(int id_siswa = 0, int id_tagihan = 0, double nominal = 0, time_t timestamp = time(0)) {
        this->id_tagihan = id_tagihan;
        this->id_siswa = id_siswa;
        this->nominal = nominal;
        this->timestamp = timestamp;
    }
};