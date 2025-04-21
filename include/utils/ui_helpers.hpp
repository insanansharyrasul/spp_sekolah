#pragma once

#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace UI {
// Color constants
namespace Color {
extern const std::string RED;
extern const std::string GREEN;
extern const std::string YELLOW;
extern const std::string BLUE;
extern const std::string MAGENTA;
extern const std::string CYAN;
extern const std::string WHITE;
extern const std::string RESET;
}  // namespace Color

// Other UI utility functions
void clrscr();
void pause_input();
void display_header(const std::string& title);
void display_footer();
std::string display_date(const time_t date);
std::string display_currency(double currency);

// Table Utility

void draw_table_separator(const std::vector<int>& column_widths);
void draw_table_header(const std::vector<std::string>& headers, const std::vector<int>& column_widths);

template <typename T>
void draw_table(const std::vector<T>& data,
                const std::vector<std::string>& headers,
                const std::vector<int>& column_widths,
                const std::function<void(const T&, const std::vector<int>&)>& row_formatter) {
    draw_table_header(headers, column_widths);

    for (const auto& item : data) {
        row_formatter(item, column_widths);
    }

    std::cout << "+";
    for (size_t i = 0; i < column_widths.size(); ++i) {
        std::cout << std::string(column_widths[i] + 2, '-');
        std::cout << ("+");
    }
    std::cout << std::endl;
}

template <typename T>
void display_sortable_table(
    std::vector<T>& data,
    const std::vector<std::string>& headers,
    const std::vector<int>& column_widths,
    std::function<void(const T&, const std::vector<int>&)> row_formatter,
    std::vector<std::function<bool(const T&, const T&)>> sort_functions,
    const std::vector<std::string>& sort_descriptions) {
    while (true) {
        clrscr();

        std::cout << Color::CYAN << "=== DATA TABLE ===" << Color::RESET << std::endl
                  << std::endl;
        draw_table(data, headers, column_widths, row_formatter);

        std::cout << std::endl
                  << "Sort options:" << std::endl;
        for (size_t i = 0; i < sort_descriptions.size(); ++i) {
            std::cout << (i + 1) << ". " << sort_descriptions[i] << std::endl;
        }
        std::cout << "0. Kembali" << std::endl;

        int choice;
        std::cout << std::endl
                  << "Pilih metode pengurutan: ";
        std::cin >> choice;

        if (choice == 0) {
            return;
        } else if (choice > 0 && choice <= static_cast<int>(sort_functions.size())) {
            std::sort(data.begin(), data.end(), sort_functions[choice - 1]);
        } else {
            std::cout << Color::RED << "Opsi tidak ada!" << Color::RESET << std::endl;
            pause_input();
        }
    }
}

// Card Utility

template <typename T>
void draw_card(const std::string& title, const T& content) {
    int width = 50;

    draw_table_separator({width});
    std::cout << "| " << std::setw(width) << std::left << title << " |" << std::endl;
    draw_table_separator({width});

    // Body
    std::stringstream ss;
    ss << content;
    std::string line;
    while (std::getline(ss, line)) {
        std::string clean_line = line;
        size_t pos = 0;
        while ((pos = clean_line.find("\033[", pos)) != std::string::npos) {
            size_t end_pos = clean_line.find("m", pos);
            if (end_pos != std::string::npos) {
                clean_line.erase(pos, end_pos - pos + 1);
            } else {
                break;
            }
        }

        // Calculate and apply padding manually
        int padding = width - clean_line.length();
        if (padding < 0) padding = 0;

        std::cout << "| " << line << std::string(padding, ' ') << " |" << std::endl;
    }

    draw_table_separator({width});
}

}  