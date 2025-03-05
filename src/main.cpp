#include <iostream>
using namespace std;

#include "menu.h"

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;
        handleUserChoice(choice);
    } while (choice != 3);

    return 0;
}