#include "payment.h"

#include <iostream>
#include <string>
using namespace std;

void payTuitionFee() {
    string studentName;
    double amount;

    cout << "Enter student name: ";
    cin >> studentName;
    cout << "Enter amount: ";
    cin >> amount;

    cout << "Payment of $" << amount << " for " << studentName << " has been processed." << endl;
}

void checkPaymentStatus() {
    string studentName;

    cout << "Enter student name: ";
    cin >> studentName;

    cout << "Payment status for " << studentName << ": Paid" << endl;
}