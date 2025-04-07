#ifndef MENU_H
#define MENU_H

#define RESET "\033[0m"
#define BLACK "\033[0;1m"
#define DARK_RED "\033[0;31m"
#define RED "\033[31;1m"
#define DARK_GREEN "\033[0;32m"
#define GREEN "\033[32;1m"
#define DARK_YELLOW "\033[0;33m"
#define YELLOW "\033[33;1m"
#define BLUE "\033[34;1m"
#define MAGENTA "\033[35;1m"
#define CYAN "\033[36;1m"
#define WHITE "\033[37;1m"

void pause_input();
void show_menu();
bool handle_user_choice(int);
void show_user();
void clrscr();
void show_account();
bool handle_account_choice(int);

enum AccountType {
    ADMIN = 1,
    SISWA = 2,
    EXIT = 3,
    GUEST = 4,
};

enum VerificationStatus {
    NEED_CONFIRMATION = -1,
    NOT_VERIFIED = 0,
    VERIFIED = 1,
    BACK = 2,
};

#endif