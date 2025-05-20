# SPP Sekolah Manager

SPP Sekolah Manager adalah aplikasi lintas platform (CLI + Qt GUI) untuk mengelola pembayaran uang sekolah (SPP). Aplikasi ini mendukung:
- Registrasi dan manajemen profil siswa
- Pengaturan pembayaran, pelacakan, dan pembaruan status
- Pembuatan dan verifikasi sertifikat
- Tanya Jawab Siswa (bertanya dan menjawab pertanyaan)
- Membatalkan tindakan admin terakhir


## Anggota
**Kelompok 12**

| Nama                        | NIM           |
|-----------------------------|---------------|
| Insan Anshary Rasul         | G6401231132   |
| Muhammad Salman Maulana     | G6401231153   |
| Daffa Naufal Mumtaz Heryadi | G6401231168   |

## Prerequisites

- C++17 compatible compiler:
  - Linux/macOS: GCC ≥ 9, Clang ≥ 10
  - Windows: MSVC (Visual Studio 2019/2022) or MinGW
- Qt 6 (Widgets module)
- CMake ≥ 3.16
- Make or Ninja (Linux/macOS)
- Git

## Folder Structure

```
│── CMakeLists.txt        # Top-level CMake build script
│── CMakePresets.json     # CMake configuration presets
│── build/                # Build output (binaries, cache, logs)
│── data/                 # Persistent data files
│   ├── students.txt
│   ├── payments.txt
│   ├── questions.txt
│   └── certificates.txt
│── include/              # Public headers (organized by module)
│   ├── application/
│   ├── controllers/
│   ├── data_structures/
│   ├── gui/
│   ├── models/
│   ├── repositories/
│   ├── services/
│   └── utils/
│── src/                  # Implementation files (mirrors include/)
│   ├── main.cpp          # Entry point
│   ├── application/
│   ├── controllers/
│   ├── gui/
│   ├── models/
│   ├── repositories/
│   ├── services/
│   └── utils/
└── tests/                # Unit and integration tests (if any)
```

## Build and Run

### Linux / macOS

```bash
git clone https://github.com/insanansharyrasul/spp_sekolah.git
cd spp_sekolah
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/lib/cmake
cmake --build .
./spp_sekolah
```

### Windows (MSVC)

```powershell
git clone https://github.com/insanansharyrasul/spp_sekolah.git
cd spp_sekolah
mkdir build; cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2022_64/lib/cmake"
cmake --build . --config Release
.
Release\spp_sekolah.exe
```

### Windows (MinGW)

```bash
git clone https://github.com/insanansharyrasul/spp_sekolah.git
cd spp_sekolah
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/mingw81_64/lib/cmake"
cmake --build .
./spp_sekolah.exe
```

> [!IMPORTANT]
> Jika anda menggunakan operasi sistem Windows, ganti versi Qt menjadi sesuai dengan apa yang anda download (Terletak di `C:\Qt\x.x.x`), Anda juga perlu menambahkan `C:\Qt\x.x.x\mingw_64\bin` pada PATH


## Konfigurasi

- Sesuaikan `CMAKE_PREFIX_PATH` ke lokasi instalasi Qt di sistem Anda.
- Data aplikasi dibaca dan disimpan di folder `data/` relatif dari direktori eksekusi.

## Panduan Kontribusi

1. Fork repository
2. Buat branch fitur (`git checkout -b feature/nama-fitur`)
3. Commit dan push perubahan
4. Buat Pull Request

Ikuti gaya kode yang ada dan sertakan unit test untuk fitur baru jika memungkinkan.

## Lisensi

Proyek ini menggunakan lisensi GNU General Public License v3.0. Lihat berkas [LICENSE](LICENSE) untuk detail.
