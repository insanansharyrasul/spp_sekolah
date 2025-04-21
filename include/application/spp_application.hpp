#pragma once
#include <controllers/admin_controller.hpp>
#include <controllers/student_controller.hpp>
#include <repositories/student_repository.hpp>
#include <services/payment_service.hpp>
#include <services/qna_service.hpp>

class UserSession {
   public:
    bool isAuthenticated;
    bool isAdmin;
    bool isStudent;
    int currentStudentId;

    UserSession();
};

class SppApplication {
   private:
    // User session
    UserSession session;

    // Repositories
    StudentRepository studentRepo;
    PaymentRepository paymentRepo;
    CertificateRepository certificateRepo;

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
