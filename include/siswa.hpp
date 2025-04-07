#ifndef SISWA_H
#define SISWA_H

enum VerificationStatus {
    NEED_CONFIRMATION = -1,
    NOT_VERIFIED = 0,
    VERIFIED = 1,
    BACK = 2,
};

int verify_siswa();
void show_menu_siswa();
VerificationStatus handle_siswa_choice(int, int);

#endif