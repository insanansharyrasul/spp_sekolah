#include <iostream>
using namespace std;

#include "menu.hpp"

int main() {
    int choice;

    bool cont = true;

    do {
        show_menu();
        cin >> choice;

        if (cin.fail()) {
            cout << "Input tidak valid, silahkan ulang lagi." << endl;
            cin.clear();
            pause_input();
            continue;
        }

        cont = handle_user_choice(choice);
    } while (cont);

    return 0;
}