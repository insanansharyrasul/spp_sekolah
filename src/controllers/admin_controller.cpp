#include <controllers/admin_controller.hpp>
#include <iomanip>
#include <iostream>

#include "utils/ui_helpers.hpp"

AdminController::AdminController(StudentService& studentService,
                                 PaymentService& paymentService,
                                 CertificateService& certService,
                                 QnAService& qnaService) : studentService(studentService),
                                                           paymentService(paymentService),
                                                           certService(certService),
                                                           qnaService(qnaService) {}

void AdminController::showDashboard() {
    while (true) {
        UI::display_header("DASBOR ADMIN");

        // Show notification if questions are pending
        int pendingQuestions = qnaService.getQueueSize();
        if (pendingQuestions > 0) {
            std::cout << UI::Color::YELLOW << "Anda memiliki " << pendingQuestions
                      << " pertanyaan yang belum dijawab!" << UI::Color::RESET << std::endl
                      << std::endl;
        }

        std::cout << "1. Lihat Semua Siswa" << std::endl;
        std::cout << "2. Lihat Semua Pembayaran" << std::endl;
        std::cout << "3. Daftarkan Siswa Baru" << std::endl;
        std::cout << "4. Atur Pembayaran" << std::endl;
        std::cout << "5. Buat Sertifikat" << std::endl;
        std::cout << "6. Batalkan Tindakan Terakhir" << std::endl;
        std::cout << "7. Jawab Pertanyaan Siswa" << std::endl;
        std::cout << "0. Keluar" << std::endl;

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
                undoLastAction();
                break;
            case 7:
                answerQuestions();
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
    std::cout << UI::Color::CYAN << "=== DAFTAR SISWA ===" << UI::Color::RESET << std::endl
              << std::endl;

    // Get all students from repository via service
    std::vector<Student> studentList = studentService.getAllStudents();

    if (studentList.empty()) {
        std::cout << UI::Color::YELLOW << "Tidak ada siswa yang ditemukan." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }

    std::vector<std::string> headers = {"ID", "Nama", "Tahun", "ID Kelas"};
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
        "Urutkan berdasarkan ID",
        "Urutkan berdasarkan Nama",
        "Urutkan berdasarkan Tahun",
        "Urutkan berdasarkan ID Kelas"};
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
    std::cout << UI::Color::CYAN << "=== RIWAYAT PEMBAYARAN ===" << UI::Color::RESET << std::endl
              << std::endl;

    // Get all payments from repository via service
    std::vector<Payment> paymentList = paymentService.getAllPayments();
    if (paymentList.empty()) {
        std::cout << UI::Color::YELLOW << "Tidak ada pembayaran yang ditemukan." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }

    std::vector<std::string> headers = {"ID", "ID Siswa", "Jumlah", "Waktu", "Tenggat", "Status"};
    std::vector<int> column_widths = {15, 12, 15, 25, 25, 10};

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
                  << "| " << std::setw(column_widths[2] + 1) << std::left << UI::display_currency(payment.getAmount())
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
        "Urutkan berdasarkan ID",
        "Urutkan berdasarkan ID Siswa",
        "Urutkan berdasarkan Jumlah",
        "Urutkan berdasarkan Waktu",
        "Urutkan berdasarkan Tenggat",
        "Urutkan berdasarkan Status"};

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
    std::cout << UI::Color::CYAN << "=== PROSES PEMBAYARAN ===" << UI::Color::RESET << std::endl
              << std::endl;

    int studentId;
    double amount;
    std::cout << "ID Siswa: ";
    std::cin >> studentId;
    std::cout << "Jumlah: ";
    std::cin >> amount;
    time_t deadline = time(0) + (30 * 24) * (60 * 60);  // 30 days from now
    std::cout << "Tenggat Pembayaran: " << std::ctime(&deadline) << std::endl;

    std::string paymentId = paymentService.setPayment(studentId, amount, deadline);
    if (!paymentId.empty()) {
        std::cout << UI::Color::GREEN << "Pembayaran telah diatur dengan ID: " << paymentId << UI::Color::RESET << std::endl;

        // Create an undo action
        auto undoFunc = [this, paymentId]() {
            return this->paymentService.deletePayment(paymentId);
        };

        actionStack.push(AdminAction(AdminAction::PROCESS_PAYMENT,
                                     paymentId,
                                     undoFunc));
    } else {
        std::cout << UI::Color::RED << "Gagal mengatur pembayaran." << UI::Color::RESET << std::endl;
    }

    UI::pause_input();
}

void AdminController::makeCertificate() {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== BUAT SERTIFIKAT ===" << UI::Color::RESET << std::endl
              << std::endl;

    std::cout << "Masukkan ID pembayaran: ";
    std::string paymentId;
    std::cin >> paymentId;

    std::string certId = certService.generateCertificate(paymentId);
    if (!certId.empty()) {
        std::cout << UI::Color::GREEN << "Sertifikat dibuat dengan ID: " << certId << UI::Color::RESET << std::endl;

        // Create an undo action
        auto undoFunc = [this, certId]() {
            return this->certService.deleteCertificate(certId);
        };

        actionStack.push(AdminAction(AdminAction::GENERATE_CERTIFICATE,
                                     certId,
                                     undoFunc));
    } else {
        std::cout << UI::Color::RED << "Gagal membuat sertifikat." << UI::Color::RESET << std::endl;
    }

    UI::pause_input();
}

void AdminController::undoLastAction() {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== BATALKAN TINDAKAN TERAKHIR ===" << UI::Color::RESET << std::endl
              << std::endl;

    if (actionStack.isEmpty()) {
        std::cout << UI::Color::YELLOW << "Tidak ada tindakan untuk dibatalkan." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }

    AdminAction lastAction = actionStack.pop();

    std::cout << "Membatalkan: " << lastAction.getActionName()
              << " (ID: " << lastAction.getId() << ")" << std::endl;

    if (lastAction.undo()) {
        std::cout << UI::Color::GREEN << "Berhasil membatalkan tindakan!" << UI::Color::RESET << std::endl;
    } else {
        std::cout << UI::Color::RED << "Gagal membatalkan tindakan." << UI::Color::RESET << std::endl;
    }

    UI::pause_input();
}

void AdminController::answerQuestions() {
    while (true) {
        UI::clrscr();
        std::cout << UI::Color::CYAN << "=== JAWAB PERTANYAAN SISWA ===" << UI::Color::RESET << std::endl
                  << std::endl;

        if (!qnaService.hasQuestionsToAnswer()) {
            std::cout << UI::Color::YELLOW << "Tidak ada pertanyaan yang menunggu untuk dijawab." << UI::Color::RESET << std::endl;
            UI::pause_input();
            return;
        }

        Question question = qnaService.getNextQuestion();
        time_t question_timestamp = question.getTimestamp();
        std::string timestamp_str = std::ctime(&question_timestamp);
        if (!timestamp_str.empty() && timestamp_str.back() == '\n')
            timestamp_str.pop_back();

        std::cout << "ID Pertanyaan: " << question.getId() << std::endl;
        std::cout << "Dari: " << question.getStudentName() << " (ID: " << question.getStudentId() << ")" << std::endl;
        std::cout << "Tanggal: " << timestamp_str << std::endl;
        std::cout << UI::Color::CYAN << "Pertanyaan: " << question.getQuestionText() << UI::Color::RESET << std::endl;
        std::cout << std::endl;

        std::cout << "Ketik jawaban Anda di bawah ini (atau ketik 'skip' untuk kembali nanti):" << std::endl;
        std::string answer;
        std::cin.ignore();
        std::getline(std::cin, answer);

        if (answer == "skip") {
            break;
        }

        if (answer.empty()) {
            std::cout << UI::Color::YELLOW << "Jawaban tidak boleh kosong. Silakan coba lagi." << UI::Color::RESET << std::endl;
            UI::pause_input();
            continue;
        }

        qnaService.answerQuestion(answer);

        std::cout << UI::Color::GREEN << "Jawaban berhasil dikirim!" << UI::Color::RESET << std::endl;

        std::cout << "\nApakah Anda ingin menjawab pertanyaan lain? (Y/N): ";
        char choice;
        std::cin >> choice;
        if (toupper(choice) != 'Y') {
            break;
        }
    }
}

// QnA GUI methods
std::vector<Question> AdminController::getPendingQuestions() {
    return qnaService.getPendingQuestions();
}

bool AdminController::answerQuestionById(int questionId, const std::string& answerText) {
    return qnaService.answerQuestionById(questionId, answerText);
}

StudentService& AdminController::getStudentService() {
    return studentService;
}

PaymentService& AdminController::getPaymentService() {
    return paymentService;
}

std::string AdminController::generateCertificate(const std::string& paymentId) {
    std::string certId = certService.generateCertificate(paymentId);
    if (!certId.empty()) {
        auto undoFunc = [this, certId]() {
            return this->certService.deleteCertificate(certId);
        };
        actionStack.push(AdminAction(AdminAction::GENERATE_CERTIFICATE, certId, undoFunc));
    }
    return certId;
}