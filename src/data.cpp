#include <data.hpp>
#include <iostream>

Siswa::Siswa(int id_siswa, std::string nama, int tahunmasuk, int id_kelas, bool jenis_kelamin, std::string alamat, std::string no_telp, std::string email) {
    this->id_siswa = id_siswa;
    this->nama = nama;
    this->tahun_masuk = tahunmasuk;
    this->id_kelas = id_kelas;
    this->jenis_kelamin = jenis_kelamin;
    this->alamat = alamat;
    this->no_telp = no_telp;
    this->email = email;
    this->nama_wali = nama_wali;
    this->statuspembayaranSPP = statuspembayaranSPP;
}

void Siswa::print_data_siswa() {
    std::cout << "ID: " << id_siswa << std::endl;
    std::cout << "Nama: " << nama << std::endl;
    std::cout << "Tahun Masuk: " << tahun_masuk << std::endl;
    std::cout << "ID Kelas: " << id_kelas << std::endl;
    std::cout << "Jenis Kelamin: " << jenis_kelamin << std::endl;
    std::cout << "Alamat: " << alamat << std::endl;
    std::cout << "No. Telp: " << no_telp << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Nama Wali: " << nama_wali << std::endl;
    if (statuspembayaranSPP == true) {
        std::cout << "Status Pembayaran SPP: Lunas" << std::endl;
    } else {
        std::cout << "Status Pembayaran SPP: Belum Lunas" << std::endl;
    }
};

AdminTU::AdminTU(int id, std::string nama, std::string username, std::string password, std::string jabatan, std::string no_telp, std::string email, std::string alamat, std::string tanggal_bergabung, time_t timestamp) {
    this->id_admin = id;
    this->nama = nama;
    this->username = username;
    this->password = password;
    this->jabatan = jabatan;
    this->no_telp = no_telp;
    this->email = email;
    this->alamat = alamat;
    this->tanggal_bergabung = tanggal_bergabung;
    this->timestamp = timestamp;
}

void AdminTU::print_data_admin() {
    std::cout << "ID: " << id_admin << std::endl;
    std::cout << "Nama: " << nama << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Jabatan: " << jabatan << std::endl;
    std::cout << "No. Telp: " << no_telp << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Alamat: " << alamat << std::endl;
    std::cout << "Tanggal Bergabung: " << tanggal_bergabung << std::endl;
};

TagihanSPP::TagihanSPP(int id, int id_siswa, int id_kelas, int tahun_ajaran, int bulan, int nominal, bool status_pembayaran) {
    this->id = id;
    this->id_siswa = id_siswa;
    this->id_kelas = id_kelas;
    this->tahun_ajaran = tahun_ajaran;
    this->bulan = bulan;
    this->nominal = nominal;
    this->status_pembayaran = status_pembayaran;
}

void TagihanSPP::print_data_tagihan_spp() {
    std::cout << "ID: " << id << std::endl;
    std::cout << "ID Siswa: " << id_siswa << std::endl;
    std::cout << "ID Kelas: " << id_kelas << std::endl;
    std::cout << "Tahun Ajaran: " << tahun_ajaran << std::endl;
    std::cout << "Bulan: " << bulan << std::endl;
    std::cout << "Nominal: " << nominal << std::endl;
    if (status_pembayaran == true) {
        std::cout << "Status Pembayaran: Lunas" << std::endl;
    } else {
        std::cout << "Status Pembayaran: Belum Lunas" << std::endl;
    }
};

Kelas::Kelas(int id_kelas, std::string nama, int tingkat, std::string jurusan, int kapasitas, int jumlah_siswa) {
    this->id_kelas = id_kelas;
    this->nama = nama;
    this->tingkat = tingkat;
    this->jurusan = jurusan;
    this->kapasitas = kapasitas;
    this->jumlah_siswa = jumlah_siswa;
    this->id_wali = id_wali;
}

void Kelas::print_data_kelas() {
    std::cout << "ID Kelas: " << id_kelas << std::endl;
    std::cout << "Nama: " << nama << std::endl;
    std::cout << "Tingkat: " << tingkat << std::endl;
    std::cout << "Jurusan: " << jurusan << std::endl;
    std::cout << "Kapasitas: " << kapasitas << std::endl;
    std::cout << "Jumlah Siswa: " << jumlah_siswa << std::endl;
    std::cout << "ID Wali Kelas: " << id_wali << std::endl;
}

PembayaranSPP::PembayaranSPP(int id_siswa, int id_tagihan, double nominal, std::string tanggalbayar) {
    this->id_tagihan = id_tagihan;
    this->id_siswa = id_siswa;
    this->nominal = nominal;
    this->tanggalbayar = tanggalbayar;
}

void PembayaranSPP::print_data_pembayaran_spp() {
    std::cout << "ID: " << id_tagihan << std::endl;
    std::cout << "ID Siswa: " << id_siswa << std::endl;
    std::cout << "ID Tagihan: " << id_tagihan << std::endl;
    std::cout << "Nominal: " << nominal << std::endl;
    std::cout << "Tanggal Bayar: " << tanggalbayar << std::endl;
};
