#include <controllers/student_controller.hpp>
#include <iostream>
#include <utils/ui_helpers.hpp>

StudentController::StudentController(StudentService& studentService,
                                     PaymentService& paymentService) : studentService(studentService),
                                                                      paymentService(paymentService) {}

void StudentController::showDashboard(int studentId) {
    while (true) {
        UI::clrscr();
        std::cout << UI::Color::CYAN << "=== STUDENT DASHBOARD ===" << UI::Color::RESET << std::endl
                  << std::endl;
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
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== MY PAYMENTS ===" << UI::Color::RESET << std::endl
              << std::endl;

    // For now, just show it's working
    std::cout << UI::Color::YELLOW << "Feature coming soon!" << UI::Color::RESET << std::endl;
    UI::pause_input();
}