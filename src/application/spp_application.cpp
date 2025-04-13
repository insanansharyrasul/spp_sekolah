#include <application/spp_application.hpp>
#include <iostream>
#include <utils/ui_helpers.hpp>

UserSession::UserSession() : isAuthenticated(false), isAdmin(false), isStudent(false), currentStudentId(-1) {}

SppApplication::SppApplication()
    : studentRepo("../data/students.txt"),
      paymentRepo("../data/payments.txt"),
      certificateRepo("../data/certificates.txt"),
      paymentService(paymentRepo, studentRepo),
      studentService(studentRepo),
      certService(paymentRepo, certificateRepo, studentRepo),
      adminController(studentService, paymentService, certService),
      studentController(studentService, paymentService) {}

void SppApplication::initialize() {
    UI::clrscr();
    std::cout << UI::Color::YELLOW << "███████╗██████╗ ██████╗  ██████╗███████╗███╗   ██╗████████╗███████╗██████╗ " << std::endl;
    std::cout << UI::Color::YELLOW << "██╔════ ██╔══██╗██╔══██╗██╔════╝██╔════╝████╗  ██║╚══██╔══╝██╔════╝██╔══██╗" << std::endl;
    std::cout << UI::Color::YELLOW << "███████ ██████╔╝██████╔╝██║     █████╗  ██╔██╗ ██║   ██║   █████╗  ██████╔╝" << std::endl;
    std::cout << UI::Color::YELLOW << "╚════██ ██╔═══╝ ██╔═══╝ ██║     ██╔══╝  ██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗" << std::endl;
    std::cout << UI::Color::YELLOW << "███████ ██║     ██║     ╚██████╗███████╗██║ ╚████║   ██║   ███████╗██║  ██║" << std::endl;
    std::cout << UI::Color::YELLOW << "╚══════╝╚═╝     ╚═╝     ╚═════╝╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝ " << std::endl;
    std::cout << std::endl;
    std::cout << "Memuat data..." << std::endl;

    if (!studentRepo.loadFromFile()) {
        std::cerr << UI::Color::RED << "Gagal memuat data siswa!" << UI::Color::RESET << std::endl;
        UI::pause_input();
        exit(1);
    }
    if (!paymentRepo.loadFromFile()) {
        std::cerr << UI::Color::RED << "Gagal memuat data pembayaran!" << UI::Color::RESET << std::endl;
        UI::pause_input();
        exit(1);
    }

    std::cout << UI::Color::GREEN << "Data berhasil dimuat!" << UI::Color::RESET << std::endl;
    UI::pause_input();
}

void SppApplication::run() {
    while (true) {
        if (!session.isAuthenticated) {
            showLoginMenu();
            continue;
        }

        if (session.isAdmin) {
            adminController.showDashboard();
            session.isAuthenticated = false;
        } else if (session.isStudent) {
            studentController.showDashboard(session.currentStudentId);
            session.isAuthenticated = false;
        }
    }
}

void SppApplication::showLoginMenu() {
    UI::clrscr();
    UI::display_header("LOGIN MENU");
    std::cout << UI::Color::CYAN
              << "1. Login as Admin" << std::endl
              << "2. Login as Student" << std::endl
              << "0. Exit" << std::endl;

    int choice;
    std::cout << "\nPilihan: ";
    std::cin >> choice;

    switch (choice) {
        case 0:
            UI::clrscr();
            std::cout << "Terima kasih telah menggunakan aplikasi ini!" << std::endl;
            exit(0);
            break;

        case 1: {
            // Simple admin authentication for quick testing
            UI::clrscr();
            std::cout << UI::Color::CYAN << "=== ADMIN LOGIN ===" << UI::Color::RESET << std::endl
                      << std::endl;

            std::string username, password;
            std::cout << "Username: ";
            std::cin >> username;
            std::cout << "Password: ";
            std::cin >> password;

            // For quick testing, use a hardcoded admin login
            if (username == "admin" && password == "admin123") {
                session.isAuthenticated = true;
                session.isAdmin = true;
                std::cout << UI::Color::GREEN << "Login berhasil!" << UI::Color::RESET << std::endl;
            } else {
                std::cout << UI::Color::RED << "Login gagal!" << UI::Color::RESET << std::endl;
                UI::pause_input();
            }
            break;
        }

        case 2: {
            // Simple student authentication for quick testing
            UI::clrscr();
            std::cout << UI::Color::CYAN << "=== STUDENT LOGIN ===" << UI::Color::RESET << std::endl
                      << std::endl;

            int studentId;
            std::cout << "Student ID: ";
            std::cin >> studentId;

            // Check if student exists using the repository
            Student* student = studentRepo.findById(studentId);
            if (student) {
                session.isAuthenticated = true;
                session.isAdmin = false;
                session.isStudent = true;
                session.currentStudentId = studentId;
                std::cout << UI::Color::GREEN << "Login berhasil! Welcome, "
                          << student->getName() << "!" << UI::Color::RESET << std::endl;
                UI::pause_input();
            } else {
                std::cout << UI::Color::RED << "Login gagal! Student tidak ditemukan."
                          << UI::Color::RESET << std::endl;
                UI::pause_input();
            }
            break;
        }

        default:
            std::cout << UI::Color::RED << "Pilihan tidak valid!" << UI::Color::RESET << std::endl;
            UI::pause_input();
    }
}