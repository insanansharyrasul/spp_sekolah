#include "menu.h"

#include <iostream>

#include "payment.h"
using namespace std;

void showMenu() {
    cout << "=== Tuition Fee Payment System ===" << endl;
    cout << "1. Pay Tuition Fee" << endl;
    cout << "2. Check Payment Status" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

void handleUserChoice(int choice) {
    switch (choice) {
        case 1:
            payTuitionFee();
            break;
        case 2:
            checkPaymentStatus();
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}