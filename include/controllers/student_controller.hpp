#pragma once
#include <services/payment_service.hpp>
#include <services/student_service.hpp>
#include <services/qna_service.hpp>
#include <services/certificate_service.hpp>
#include <models/payment.hpp>
#include <vector>

class StudentController {
   private:
    StudentService& studentService;
    PaymentService& paymentService;
    QnAService& qnaService;
    CertificateService& certificateService;

   public:
    StudentController(StudentService& studentService, 
                      PaymentService& paymentService,
                      QnAService& qnaService,
                      CertificateService& certificateService);

    // UI handling methods
    void showDashboard(int studentId);
    void viewProfile(int studentId);
    void viewPayments(int studentId);
    
    // QnA methods
    void askQuestion(int studentId);
    void viewAnsweredQuestions(int studentId);
    
    // Certificate methods
    void verifyCertificate(int studentId);
    
    // Accessor methods
    StudentService& getStudentService() const;
    bool submitQuestion(int studentId, const std::string& question);
    std::vector<Payment> getPaymentHistory(int studentId);
};