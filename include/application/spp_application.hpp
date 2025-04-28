#pragma once
#include <controllers/admin_controller.hpp>
#include <controllers/student_controller.hpp>
#include <repositories/student_repository.hpp>
#include <repositories/payment_repository.hpp>
#include <repositories/certificate_repository.hpp>
#include <repositories/question_repository.hpp>
#include <services/payment_service.hpp>
#include <services/qna_service.hpp>

class UserSessionCLI {
   public:
    bool isAuthenticated;
    bool isAdmin;
    bool isStudent;
    int currentStudentId;

    UserSessionCLI();
};

class SppApplication {
   private:
    // User session
    UserSessionCLI session;

    // Repositories
    StudentRepository studentRepo;
    PaymentRepository paymentRepo;
    CertificateRepository certificateRepo;
    QuestionRepository questionRepo;

    // Services
    StudentService studentService;
    PaymentService paymentService;
    CertificateService certService;
    QnAService qnaService;

    // Controllers
    AdminController adminController;
    StudentController studentController;

   public:
    SppApplication();

    void initialize();
    void run();
    void showLoginMenu();
};
