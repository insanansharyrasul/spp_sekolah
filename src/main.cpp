#include <iostream>
using namespace std;

#include "menu.h"

int main() {
    int choice;

    do {
        show_menu();
        cin >> choice;
        handle_user_choice(choice);
    } while (choice != 3);

    return 0;
}