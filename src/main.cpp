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
            cin.clear();
            cin.ignore();
            cout << "Input tidak valid, silahkan ulang lagi." << endl;
            continue;
        }

        cont = handle_user_choice(choice);
    } while (cont);

    return 0;
}