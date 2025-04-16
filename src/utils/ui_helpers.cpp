#include <iostream>
#include <limits>
#include <utils/ui_helpers.hpp>
#include <vector>
#include <functional>
#include <models/student.hpp> 
#include <models/payment.hpp> 
#include <iomanip>

namespace UI {
// ANSI color code definitions
namespace Color {
    const std::string RED = "\033[1;31m";      
    const std::string GREEN = "\033[1;32m";    
    const std::string YELLOW = "\033[1;33m";   
    const std::string BLUE = "\033[1;34m";     
    const std::string MAGENTA = "\033[1;35m";  
    const std::string CYAN = "\033[1;36m";     
    const std::string WHITE = "\033[1;37m";    
    const std::string RESET = "\033[0m";
}

// Other UI utility functions
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

std::string display_date(const time_t date) {
    return ctime(&date);
}

std::string display_currency(double currency) {
    std::ostringstream oss;

    oss.imbue(std::locale("id_ID.UTF-8"));

    oss << std::fixed << std::setprecision(2) << currency;
    return oss.str();
}


// Table Utility
void draw_table_separator(const std::vector<int>& column_widths) {
    for (const auto& width : column_widths) {
        std::cout << "+";
        for (int i = 0; i < width + 2; ++i) {
            std::cout << "-";
        }
    }
    std::cout << "+" << std::endl;
}

void draw_table_header(const std::vector<std::string>& headers, const std::vector<int>& column_widths) {
    draw_table_separator(column_widths);
    std::cout << "|";
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << " " << headers[i];
        for (int j = headers[i].length(); j < column_widths[i]; ++j) {
            std::cout << " ";
        }
        std::cout << " |";
    }
    std::cout << std::endl;
    draw_table_separator(column_widths);
}

}  // namespace UI