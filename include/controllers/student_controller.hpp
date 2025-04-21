#pragma once
#include <services/payment_service.hpp>
#include <services/student_service.hpp>
#include <services/qna_service.hpp>

class StudentController {
   private:
    StudentService& studentService;
    PaymentService& paymentService;
    QnAService& qnaService;

   public:
    StudentController(StudentService& studentService, 
                      PaymentService& paymentService,
                      QnAService& qnaService);

    // UI handling methods
    void showDashboard(int studentId);
    void viewProfile(int studentId);
    void viewPayments(int studentId);
    
    // QnA methods
    void askQuestion(int studentId);
    void viewAnsweredQuestions(int studentId);
};