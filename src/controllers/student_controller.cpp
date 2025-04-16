#include <controllers/student_controller.hpp>
#include <iomanip>
#include <iostream>
#include <utils/ui_helpers.hpp>

StudentController::StudentController(StudentService& studentService,
                                     PaymentService& paymentService) : studentService(studentService),
                                                                       paymentService(paymentService) {}

void StudentController::showDashboard(int studentId) {
    while (true) {
        UI::clrscr();
        std::cout << UI::Color::CYAN << "=== STUDENT DASHBOARD ===" << UI::Color::RESET << std::endl;
        std::cout << std::endl;
        std::cout << "Halo, "
                  << UI::Color::YELLOW << studentService.getStudentName(studentId) << UI::Color::RESET
                  << "! Apakah ada yang ingin lakukan?"
                  << std::endl;
        std::cout << std::endl;
        std::cout << "1. View My Profile" << std::endl;
        std::cout << "2. View My Payments" << std::endl;
        std::cout << "0. Logout" << std::endl;

        int choice;
        std::cout << "\nPilihan: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                viewProfile(studentId);
                break;
            case 2:
                viewPayments(studentId);
                break;
            case 0:
                return;  // Return to main menu/logout
            default:
                std::cout << UI::Color::RED << "Pilihan tidak valid!" << UI::Color::RESET << std::endl;
                UI::pause_input();
        }
    }
}

// Implement minimal versions of these methods
void StudentController::viewProfile(int studentId) {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== MY PROFILE ===" << UI::Color::RESET << std::endl
              << std::endl;

    // Get student details from repository via service
    Student* student = studentService.getStudentById(studentId);
    if (student->getId() == 0) {
        std::cout << UI::Color::RED << "Student not found!" << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }

    // Display student details
    UI::draw_card("Student Details", *student);

    UI::pause_input();
}

void StudentController::viewPayments(int studentId) {
    while (true) {
        UI::clrscr();
        std::cout << UI::Color::CYAN << "=== MY PAYMENTS ===" << UI::Color::RESET << std::endl
                << std::endl;

        // Get payment details from repository via service
        std::vector<Payment> payments = paymentService.getStudentPaymentHistory(studentId);
        if (payments.empty()) {
            std::cout << UI::Color::RED << "No payment history found!" << UI::Color::RESET << std::endl;
            UI::pause_input();
            return;
        }

        // Display latest payment by default
        std::cout << UI::Color::YELLOW << "Latest Payment:" << UI::Color::RESET << std::endl;
        UI::draw_card("Payment Details", payments[0]);  // Assuming first entry is the latest
        
        // Menu options
        std::cout << "\n1. View Payment by Month/Year" << std::endl;
        std::cout << "0. Back to Dashboard" << std::endl;
        
        int choice;
        std::cout << "\nPilihan: ";
        std::cin >> choice;
        
        if (choice == 0) {
            return;
        } else if (choice == 1) {
            int month, year;
            std::cout << "Enter Month (1-12): ";
            std::cin >> month;
            std::cout << "Enter Year: ";
            std::cin >> year;
            
            UI::clrscr();
            std::cout << UI::Color::CYAN << "=== PAYMENTS FOR " << month << "/" << year << " ===" << UI::Color::RESET << std::endl << std::endl;
            
            bool found = false;
            for (const auto& p : payments) {
                // Assuming Payment has month and year getters or can be extracted from date
                if (p.getMonth() == month && p.getYear() == year) {
                    UI::draw_card("Payment Details", p);
                    found = true;
                }
            }
            
            if (!found) {
                std::cout << UI::Color::RED << "No payments found for the specified month and year." << UI::Color::RESET << std::endl;
            }
            
            UI::pause_input();
        } else {
            std::cout << UI::Color::RED << "Invalid choice!" << UI::Color::RESET << std::endl;
            UI::pause_input();
        }
    }
}