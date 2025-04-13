#include <controllers/admin_controller.hpp>
#include <iomanip>
#include <iostream>

#include "utils/ui_helpers.hpp"

AdminController::AdminController(StudentService& studentService,
                                 PaymentService& paymentService) : studentService(studentService),
                                                                   paymentService(paymentService) {}

void AdminController::showDashboard() {
    while (true) {
        UI::display_header("ADMIN DASHBOARD");
        std::cout << "1. Register New Student" << std::endl;
        std::cout << "2. View All Students" << std::endl;
        std::cout << "4. View All Payments" << std::endl;
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
    std::vector<Student> studentList = studentService.getAllStudents();

    if (studentList.empty()) {
        std::cout << UI::Color::YELLOW << "No students found." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }

    std::vector<std::string> headers = {"ID", "Name", "Year", "Class ID"};
    std::vector<int> column_widths = {6, 20, 10, 10};
    auto row_formater = [](const Student& student, const std::vector<int>& column_widths) {
        std::cout << "| " << std::setw(column_widths[0] + 1) << std::left << student.getId()
                  << "| " << std::setw(column_widths[1] + 1) << std::left << student.getName()
                  << "| " << std::setw(column_widths[2] + 1) << std::left << student.getYearRegistered()
                  << "| " << std::setw(column_widths[3] + 1) << std::left << student.getClassId()
                  << "|" << std::endl;
    };
    std::vector<std::function<bool(const Student&, const Student&)>> sort_functions = {
        [](const Student& a, const Student& b) { return a.getId() < b.getId(); },
        [](const Student& a, const Student& b) { return a.getName() < b.getName(); },
        [](const Student& a, const Student& b) { return a.getYearRegistered() < b.getYearRegistered(); },
        [](const Student& a, const Student& b) { return a.getClassId() < b.getClassId(); }};
    std::vector<std::string> sort_labels = {
        "Sort by ID",
        "Sort by Name",
        "Sort by Year",
        "Sort by Class ID"};
    UI::display_sortable_table<Student>(studentList,
                                        headers,
                                        column_widths,
                                        row_formater,
                                        sort_functions,
                                        sort_labels);

    UI::pause_input();
}

void AdminController::viewAllPayments() {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== PAYMENT HISTORY ===" << UI::Color::RESET << std::endl
              << std::endl;

    // Get all payments from repository via service
    std::vector<Payment> paymentList = paymentService.getAllPayments();
    if (paymentList.empty()) {
        std::cout << UI::Color::YELLOW << "No payments found." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }

    std::vector<std::string> headers = {"ID", "Student ID", "Amount", "Timestamp", "Deadline", "Status"};
    std::vector<int> column_widths = {6, 12, 8, 20, 20, 10};

    auto row_formater = [](const Payment& payment, const std::vector<int>& column_widths) {
        time_t timestamp = payment.getTimestamp();
        time_t deadline = payment.getDeadline();

        std::string timestamp_str = std::ctime(&timestamp);
        std::string deadline_str = std::ctime(&deadline);

        if (!timestamp_str.empty() && timestamp_str.back() == '\n')
            timestamp_str.pop_back();
        if (!deadline_str.empty() && deadline_str.back() == '\n')
            deadline_str.pop_back();

        std::string status = payment.getIsPaid()
                                 ? UI::Color::GREEN + "Paid" + UI::Color::RESET
                                 : UI::Color::RED + "Unpaid" + UI::Color::RESET;

        std::cout << "| " << std::setw(column_widths[0]) << std::left << payment.getId()
                  << "| " << std::setw(column_widths[1]) << std::left << payment.getStudentId()
                  << "| " << std::setw(column_widths[2]) << std::left << payment.getAmount()
                  << "| " << std::setw(column_widths[3]) << std::left << timestamp_str
                  << "| " << std::setw(column_widths[4]) << std::left << deadline_str
                  << "| " << std::setw(column_widths[5]) << std::left << status
                  << "|" << std::endl;
    };

    std::vector<std::function<bool(const Payment&, const Payment&)>> sort_functions = {
        [](const Payment& a, const Payment& b) { return a.getId() < b.getId(); },
        [](const Payment& a, const Payment& b) { return a.getStudentId() < b.getStudentId(); },
        [](const Payment& a, const Payment& b) { return a.getAmount() < b.getAmount(); },
        [](const Payment& a, const Payment& b) { return a.getTimestamp() < b.getTimestamp(); },
        [](const Payment& a, const Payment& b) { return a.getDeadline() < b.getDeadline(); },
        [](const Payment& a, const Payment& b) { return a.getIsPaid() < b.getIsPaid(); }};

    std::vector<std::string> sort_labels = {
        "Sort by ID",
        "Sort by Student ID",
        "Sort by Amount",
        "Sort by Timestamp",
        "Sort by Deadline",
        "Sort by Status"};

    UI::display_sortable_table<Payment>(paymentList,
                                        headers,
                                        column_widths,
                                        row_formater,
                                        sort_functions,
                                        sort_labels);

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