#include <iostream>
#include <limits>
#include <utils/ui_helpers.hpp>

namespace UI {
// ANSI color code definitions
namespace Color {
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string RESET = "\033[0m";
}  // namespace Color

void clrscr() {
    system("clear");  // Or system("cls") with Windows detection
}

void pause_input() {
    std::cout << "\nTekan enter untuk melanjutkan...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void display_header(const std::string& title) {
    clrscr();
    std::cout << Color::CYAN << "===== " << title << " =====" << Color::RESET << std::endl
              << std::endl;
}

void display_footer() {
    std::cout << std::endl
              << Color::CYAN << "=====================" << Color::RESET << std::endl;
}
}  // namespace UI