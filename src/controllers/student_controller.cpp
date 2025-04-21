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
        std::cout << UI::Color::CYAN << "=== STUDENT DASHBOARD ===" << UI::Color::RESET << std::endl;
        std::cout << std::endl;
        std::cout << "Halo, "
                  << UI::Color::YELLOW << studentService.getStudentName(studentId) << UI::Color::RESET
                  << "! Apakah ada yang ingin lakukan?"
                  << std::endl;
        std::cout << std::endl;
        std::cout << "1. View My Profile" << std::endl;
        std::cout << "2. View My Payments" << std::endl;
        std::cout << "3. Ask a Question" << std::endl;
        std::cout << "4. View Answered Questions" << std::endl;
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
            std::cout << UI::Color::CYAN << "=== PAYMENTS FOR " << month << "/" << year << " ===" << UI::Color::RESET << std::endl
                      << std::endl;

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

void StudentController::askQuestion(int studentId) {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== ASK A QUESTION ===" << UI::Color::RESET << std::endl
              << std::endl;

    std::string studentName = studentService.getStudentName(studentId);
    std::string question;
    
    std::cout << "Type your question below (press Enter when done):" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, question);
    
    if (question.empty()) {
        std::cout << UI::Color::YELLOW << "Question cannot be empty." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }
    
    int questionId = qnaService.submitQuestion(studentId, studentName, question);
    
    std::cout << UI::Color::GREEN << "Your question has been submitted with ID: " << questionId << UI::Color::RESET << std::endl;
    std::cout << "An admin will answer your question soon." << std::endl;
    UI::pause_input();
}

void StudentController::viewAnsweredQuestions(int studentId) {
    UI::clrscr();
    std::cout << UI::Color::CYAN << "=== MY ANSWERED QUESTIONS ===" << UI::Color::RESET << std::endl
              << std::endl;
    
    auto answeredQuestions = qnaService.getAnsweredQuestionsForStudent(studentId);
    
    if (answeredQuestions.empty()) {
        std::cout << UI::Color::YELLOW << "You have no answered questions yet." << UI::Color::RESET << std::endl;
        UI::pause_input();
        return;
    }
    
    for (const auto& question : answeredQuestions) {
        time_t question_timestamp = question.getTimestamp();
        std::string timestamp_str = std::ctime(&question_timestamp);
        if (!timestamp_str.empty() && timestamp_str.back() == '\n')
            timestamp_str.pop_back();
            
        std::cout << UI::Color::YELLOW << "Question ID: " << question.getId() << UI::Color::RESET << std::endl;
        std::cout << "Date: " << timestamp_str << std::endl;
        std::cout << UI::Color::CYAN << "Q: " << question.getQuestionText() << UI::Color::RESET << std::endl;
        std::cout << UI::Color::GREEN << "A: " << question.getAnswer() << UI::Color::RESET << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
    
    UI::pause_input();
}