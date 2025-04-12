// src/controllers/admin_controller.cpp
#include "controllers/admin_controller.hpp"

#include <iostream>

#include "utils/ui_helpers.hpp"

AdminController::AdminController(StudentService& studentService) : studentService(studentService) {}
                                //  PaymentService& paymentService,
                                //  CertificateService& certService) : studentService(studentService) {}
// paymentService(paymentService),
// certService(certService) {}

void AdminController::showDashboard() {
    while (true) {
        UI::display_header("ADMIN DASHBOARD");
        std::cout << "1. Register New Student" << std::endl;
        std::cout << "2. View All Students" << std::endl;
        std::cout << "3. Process Payment" << std::endl;
        std::cout << "4. View Payment History" << std::endl;
        std::cout << "0. Logout" << std::endl;

        int choice;
        std::cout << "\nPilihan: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerNewStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                viewAllPayments();
                break;
            case 4:
                processPayment();
                break;
            case 0:
                return;
            default:
                std::cout << UI::Color::RED << "Pilihan tidak valid!" << UI::Color::RESET << std::endl;
                UI::pause_input();
        }
    }
}

void AdminController::registerNewStudent() {
    UI::display_header("PENDAFTARAN SISWA BARU");

    std::string name;
    int classId, year;

    std::cout << "Nama Siswa: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Tahun Masuk: ";
    std::cin >> year;

    std::cout << "ID Kelas: ";
    std::cin >> classId;

    if (studentService.registerStudent(name, year, classId)) {
        std::cout << UI::Color::GREEN << "Siswa berhasil didaftarkan!" << UI::Color::RESET << std::endl;
    } else {
        std::cout << UI::Color::RED << "Gagal mendaftarkan siswa." << UI::Color::RESET << std::endl;
    }

    UI::pause_input();
}

void AdminController::viewAllStudents() {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== STUDENT LIST ===" << UI::Color::RESET << std::endl
              << std::endl;

    // Get all students from repository via service
    // For now, just show it's working
    std::cout << UI::Color::YELLOW << "Feature coming soon!" << UI::Color::RESET << std::endl;
    UI::pause_input();
}

void AdminController::viewAllPayments() {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== PAYMENT HISTORY ===" << UI::Color::RESET << std::endl
              << std::endl;

    // Get all payments from repository via service
    // For now, just show it's working
    std::cout << UI::Color::YELLOW << "Feature coming soon!" << UI::Color::RESET << std::endl;
    UI::pause_input();
}

void AdminController::processPayment() {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== PROCESS PAYMENT ===" << UI::Color::RESET << std::endl
              << std::endl;

    // Get all payments from repository via service
    // For now, just show it's working
    std::cout << UI::Color::YELLOW << "Feature coming soon!" << UI::Color::RESET << std::endl;
    UI::pause_input();
}

// Implement other controller methods