#ifndef SISWA_H
#define SISWA_H
#include "menu.hpp"
#include <iostream>

int verify_siswa(std::string&);
void show_menu_siswa(std::string);
VerificationStatus handle_siswa_choice(int, int);

#endif