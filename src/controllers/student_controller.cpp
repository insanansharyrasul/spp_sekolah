#include <controllers/student_controller.hpp>
#include <iomanip>
#include <iostream>
#include <utils/ui_helpers.hpp>

StudentController::StudentController(StudentService& studentService,
                                     PaymentService& paymentService,
                                     QnAService& qnaService) : studentService(studentService),
                                                              paymentService(paymentService),
                                                              qnaService(qnaService) {}

void StudentController::showDashboard(int studentId) {
    while (true) {
        UI::clrscr();
        std::cout << UI::Color::CYAN << "=== DASBOR SISWA ===" << UI::Color::RESET << std::endl;
        std::cout << std::endl;
        std::cout << "Halo, "
                  << UI::Color::YELLOW << studentService.getStudentName(studentId) << UI::Color::RESET
                  << "! Apakah ada yang ingin lakukan?"
                  << std::endl;
        std::cout << std::endl;
        std::cout << "1. Lihat Profil Saya" << std::endl;
        std::cout << "2. Lihat Pembayaran Saya" << std::endl;
        std::cout << "3. Ajukan Pertanyaan" << std::endl;
        std::cout << "4. Lihat Pertanyaan yang Sudah Dijawab" << std::endl;
        std::cout << "0. Keluar" << std::endl;

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
            case 3:
                askQuestion(studentId);
                break;
            case 4:
                viewAnsweredQuestions(studentId);
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
    std::cout << UI::Color::CYAN << "=== PROFIL SAYA ===" << UI::Color::RESET << std::endl
              << std::endl;

    // Get student details from repository via service
    Student* student = studentService.getStudentById(studentId);
    if (student->getId() == 0) {
        std::cout << UI::Color::RED << "Siswa tidak ditemukan!" << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }

    // Display student details
    UI::draw_card("Detail Siswa", *student);

    UI::pause_input();
}

void StudentController::viewPayments(int studentId) {
    while (true) {
        UI::clrscr();
        std::cout << UI::Color::CYAN << "=== PEMBAYARAN SAYA ===" << UI::Color::RESET << std::endl
                  << std::endl;

        // Get payment details from repository via service
        std::vector<Payment> payments = paymentService.getStudentPaymentHistory(studentId);
        if (payments.empty()) {
            std::cout << UI::Color::RED << "Tidak ada riwayat pembayaran ditemukan!" << UI::Color::RESET << std::endl;
            UI::pause_input();
            return;
        }

        // Display latest payment by default
        std::cout << UI::Color::YELLOW << "Pembayaran Terbaru:" << UI::Color::RESET << std::endl;
        UI::draw_card("Detail Pembayaran", payments[0]);  // Assuming first entry is the latest

        // Menu options
        std::cout << "\n1. Lihat Pembayaran berdasarkan Bulan/Tahun" << std::endl;
        std::cout << "0. Kembali ke Dasbor" << std::endl;

        int choice;
        std::cout << "\nPilihan: ";
        std::cin >> choice;

        if (choice == 0) {
            return;
        } else if (choice == 1) {
            int month, year;
            std::cout << "Masukkan Bulan (1-12): ";
            std::cin >> month;
            std::cout << "Masukkan Tahun: ";
            std::cin >> year;

            UI::clrscr();
            std::cout << UI::Color::CYAN << "=== PEMBAYARAN UNTUK " << month << "/" << year << " ===" << UI::Color::RESET << std::endl
                      << std::endl;

            bool found = false;
            for (const auto& p : payments) {
                // Assuming Payment has month and year getters or can be extracted from date
                if (p.getMonth() == month && p.getYear() == year) {
                    UI::draw_card("Detail Pembayaran", p);
                    found = true;
                }
            }

            if (!found) {
                std::cout << UI::Color::RED << "Tidak ada pembayaran yang ditemukan untuk bulan dan tahun yang ditentukan." << UI::Color::RESET << std::endl;
            }

            UI::pause_input();
        } else {
            std::cout << UI::Color::RED << "Pilihan tidak valid!" << UI::Color::RESET << std::endl;
            UI::pause_input();
        }
    }
}

void StudentController::askQuestion(int studentId) {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== AJUKAN PERTANYAAN ===" << UI::Color::RESET << std::endl
              << std::endl;

    std::string studentName = studentService.getStudentName(studentId);
    std::string question;
    
    std::cout << "Ketik pertanyaan Anda di bawah ini (tekan Enter jika selesai):" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, question);
    
    if (question.empty()) {
        std::cout << UI::Color::YELLOW << "Pertanyaan tidak boleh kosong." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }
    
    int questionId = qnaService.submitQuestion(studentId, studentName, question);
    
    std::cout << UI::Color::GREEN << "Pertanyaan Anda telah dikirim dengan ID: " << questionId << UI::Color::RESET << std::endl;
    std::cout << "Admin akan segera menjawab pertanyaan Anda." << std::endl;
    UI::pause_input();
}

void StudentController::viewAnsweredQuestions(int studentId) {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== PERTANYAAN YANG SUDAH DIJAWAB ===" << UI::Color::RESET << std::endl
              << std::endl;
    
    auto answeredQuestions = qnaService.getAnsweredQuestionsForStudent(studentId);
    
    if (answeredQuestions.empty()) {
        std::cout << UI::Color::YELLOW << "Anda belum memiliki pertanyaan yang dijawab." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }
    
    for (const auto& question : answeredQuestions) {
        time_t question_timestamp = question.getTimestamp();
        std::string timestamp_str = std::ctime(&question_timestamp);
        if (!timestamp_str.empty() && timestamp_str.back() == '\n')
            timestamp_str.pop_back();
            
        std::cout << UI::Color::YELLOW << "ID Pertanyaan: " << question.getId() << UI::Color::RESET << std::endl;
        std::cout << "Tanggal: " << timestamp_str << std::endl;
        std::cout << UI::Color::CYAN << "Q: " << question.getQuestionText() << UI::Color::RESET << std::endl;
        std::cout << UI::Color::GREEN << "A: " << question.getAnswer() << UI::Color::RESET << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
    
    UI::pause_input();
}

// Returns a reference to the student service
StudentService& StudentController::getStudentService() const {
    return studentService;
}

// Submits a question from a student to the QnA service
bool StudentController::submitQuestion(int studentId, const std::string& question) {
    if (question.empty()) {
        return false;
    }
    
    std::string studentName = studentService.getStudentName(studentId);
    int questionId = qnaService.submitQuestion(studentId, studentName, question);
    
    // If questionId > 0, the question was successfully submitted
    return questionId > 0;
}