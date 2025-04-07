#include <iostream>
using namespace std;

#include <admin.hpp>
#include <limits>
#include <siswa.hpp>

#include "menu.hpp"

int main() {
    int choice;

    while (true) {
        show_account();
        if (!(cin >> choice)) {
            cout << "\nInput tidak valid. Silakan coba lagi." << endl;
            cin.clear();
            pause_input();
            clrscr();
            continue;
        }

        VerificationStatus status = NEED_CONFIRMATION;
        switch (choice) {
            case 1: {
                show_menu_admin();
                break;
            }
            case 2: {
                bool verification_failed = false;
                while ((status == VERIFIED || status == NEED_CONFIRMATION) && !verification_failed) {
                    int id_siswa = -1;
                    if (status == NEED_CONFIRMATION) {
                        id_siswa = verify_siswa();
                        if (id_siswa != -1) {
                            status = VERIFIED;
                        } else {
                            status = NOT_VERIFIED;
                            verification_failed = true;
                            break;
                        }
                    }

                    if (verification_failed || status == NOT_VERIFIED) {
                        break;
                    }

                    show_menu_siswa();
                    int output;
                    cin >> output;
                    VerificationStatus session = handle_siswa_choice(output, id_siswa);
                    if (session == BACK) {
                        break;
                    }
                }
                break;
            }
            case 3: {
                cout << "Exiting..." << endl;
                exit(0);
                break;
            }
            default: {
                cout << "Pilihan tidak ada, silahkan ulang lagi." << endl;
                pause_input();
                continue;
            }
        }
    }
    return 0;
}