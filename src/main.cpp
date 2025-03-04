#include <iostream>

#include "menu.h"

int main() {
    int choice;

    do {
        showMenu();
        std::cin >> choice;
        handleUserChoice(choice);
    } while (choice != 3);

    return 0;
}