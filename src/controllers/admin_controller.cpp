#include <controllers/admin_controller.hpp>
#include <iomanip>
#include <iostream>

#include "utils/ui_helpers.hpp"

AdminController::AdminController(StudentService& studentService,
                                 PaymentService& paymentService,
                                 CertificateService& certService) : studentService(studentService),
                                                                    paymentService(paymentService),
                                                                    certService(certService) {}

void AdminController::showDashboard() {
    while (true) {
        UI::display_header("ADMIN DASHBOARD");
        std::cout << "1. View All Students" << std::endl;
        std::cout << "2. View All Payments" << std::endl;
        std::cout << "3. Register New Student" << std::endl;
        std::cout << "4. Set Payment" << std::endl;
        std::cout << "5. Generate Certificate" << std::endl;
        std::cout << "6. Undo Last Action" << std::endl;  // New option
        std::cout << "0. Logout" << std::endl;

        int choice;
        std::cout << "\nPilihan: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                viewAllStudents();
                break;
            case 2:
                viewAllPayments();
                break;
            case 3:
                registerNewStudent();
                break;
            case 4:
                setPayment();
                break;
            case 5:
                makeCertificate();
                break;
            case 6:
                undoLastAction();  // New case
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
        
        // Get the highest ID (assuming it's the one we just added)
        int studentId = 0;
        for (const auto& student : studentService.getAllStudents()) {
            if (student.getId() > studentId) {
                studentId = student.getId();
            }
        }
        
        // Create an undo action
        auto undoFunc = [this, studentId]() {
            return this->studentService.deleteStudent(studentId);
        };
        
        actionStack.push(AdminAction(AdminAction::REGISTER_STUDENT, 
                                    std::to_string(studentId), 
                                    undoFunc));
        
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
    std::vector<int> column_widths = {15, 12, 8, 25, 25, 10};

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
                                 ? "Paid"
                                 : "Unpaid";

        std::string paidColor = payment.getIsPaid() ? UI::Color::GREEN : UI::Color::RED;

        std::cout << "| " << std::setw(column_widths[0] + 1) << std::left << payment.getId()
                  << "| " << std::setw(column_widths[1] + 1) << std::left << payment.getStudentId()
                  << "| " << std::setw(column_widths[2] + 1) << std::left << payment.getAmount()
                  << "| " << std::setw(column_widths[3] + 1) << std::left << timestamp_str
                  << "| " << std::setw(column_widths[4] + 1) << std::left << deadline_str
                  << "| " << paidColor << std::setw(column_widths[5] + 1) << std::left << status << UI::Color::RESET
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

void AdminController::setPayment() {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== PROCESS PAYMENT ===" << UI::Color::RESET << std::endl
              << std::endl;

    int studentId;
    double amount;
    std::cout << "Student ID: ";
    std::cin >> studentId;
    std::cout << "Amount: ";
    std::cin >> amount;
    time_t deadline = time(0) + (30 * 24) * (60 * 60);  // 30 days from now
    std::cout << "Payment Deadline: " << std::ctime(&deadline) << std::endl;

    std::string paymentId = paymentService.setPayment(studentId, amount, deadline);
    if (!paymentId.empty()) {
        std::cout << UI::Color::GREEN << "Payment has been set with ID: " << paymentId << UI::Color::RESET << std::endl;
        
        // Create an undo action
        auto undoFunc = [this, paymentId]() {
            return this->paymentService.deletePayment(paymentId);
        };
        
        actionStack.push(AdminAction(AdminAction::PROCESS_PAYMENT, 
                                    paymentId, 
                                    undoFunc));
    } else {
        std::cout << UI::Color::RED << "Failed to set payment." << UI::Color::RESET << std::endl;
    }

    UI::pause_input();
}

void AdminController::makeCertificate() {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== MAKE CERTIFICATE ===" << UI::Color::RESET << std::endl
              << std::endl;

    std::cout << "Input payment ID: ";
    std::string paymentId;
    std::cin >> paymentId;

    std::string certId = certService.generateCertificate(paymentId);
    if (!certId.empty()) {
        std::cout << UI::Color::GREEN << "Certificate generated with ID: " << certId << UI::Color::RESET << std::endl;
        
        // Create an undo action
        auto undoFunc = [this, certId]() {
            return this->certService.deleteCertificate(certId);
        };
        
        actionStack.push(AdminAction(AdminAction::GENERATE_CERTIFICATE, 
                                    certId, 
                                    undoFunc));
    } else {
        std::cout << UI::Color::RED << "Failed to generate certificate." << UI::Color::RESET << std::endl;
    }
    
    UI::pause_input();
}

void AdminController::undoLastAction() {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== UNDO LAST ACTION ===" << UI::Color::RESET << std::endl
              << std::endl;
    
    if (actionStack.isEmpty()) {
        std::cout << UI::Color::YELLOW << "No actions to undo." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }
    
    AdminAction lastAction = actionStack.pop();
    
    std::cout << "Undoing: " << lastAction.getActionName() 
              << " (ID: " << lastAction.getId() << ")" << std::endl;
    
    if (lastAction.undo()) {
        std::cout << UI::Color::GREEN << "Successfully undid the action!" << UI::Color::RESET << std::endl;
    } else {
        std::cout << UI::Color::RED << "Failed to undo the action." << UI::Color::RESET << std::endl;
    }
    
    UI::pause_input();
}

// Implement other controller methods