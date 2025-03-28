#ifndef SISWA_H
#define SISWA_H
#include <ctime>
#include <string>

class Siswa {
   public:
    int id_siswa;
    std::string nama;
    int tahun_masuk;
    int id_kelas;
    bool jenis_kelamin;
    std::string alamat;
    std::string no_telp;
    std::string email;
    std::string nama_wali;
    bool statuspembayaranSPP;
    Siswa(int, std::string, int, int, bool, std::string, std::string, std::string);
    void print_data_siswa();
};

class AdminTU {
   public:
    int id_admin;
    std::string nama;
    std::string username;
    std::string password;
    std::string jabatan;
    std::string no_telp;
    std::string email;
    std::string alamat;
    std::string tanggal_bergabung;
    time_t timestamp;
    AdminTU(int, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, time_t);
    void print_data_admin();
};

class TagihanSPP {
   public:
    int id;
    int id_siswa;
    int id_kelas;
    int tahun_ajaran;
    int bulan;
    int nominal;
    bool status_pembayaran;
    TagihanSPP(int, int, int, int, int, int, bool);
    void print_data_tagihan_spp();
};

class Kelas {
    int id_kelas;
    std::string nama;
    int tingkat;
    std::string jurusan;
    int kapasitas;
    int jumlah_siswa;
    int id_wali;
    Kelas(int, std::string, int, std::string, int, int);
    void print_data_kelas();
};

class PembayaranSPP {
    public:
    PembayaranSPP(int, int, double, std::string);
    int id_siswa;
    int id_tagihan;
    double nominal;
    std::string tanggalbayar;
    void print_data_pembayaran_spp();
};

#endif