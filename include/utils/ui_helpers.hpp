#pragma once

#include <string>

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
// Add other UI helper functions as needed
}  // namespace UI