#pragma once

void pause_input();
void show_menu();
bool handle_user_choice(int);
void show_user();
void clrscr();
void show_account();
bool handle_account_choice(int);

enum VerificationStatus {
    NEED_CONFIRMATION = -1,
    NOT_VERIFIED = 0,
    VERIFIED = 1,
    BACK = 2,
};