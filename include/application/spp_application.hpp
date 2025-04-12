#include <controllers/admin_controller.hpp>
#include <controllers/student_controller.hpp>
#include <repositories/student_repository.hpp>
#include <services/payment_service.hpp>

class UserSession {
    public:
        bool isAuthenticated;
        bool isAdmin;
        int currentStudentId;
    
    UserSession() : isAuthenticated(false), isAdmin(false), currentStudentId(-1) {}
};

class SppApplication {
   private:

    // User session
    UserSession session;

    // Repositories
    StudentRepository studentRepo;
    // PaymentRepository paymentRepo;

    // Services
    StudentService studentService;
    // PaymentService paymentService;
    // CertificateService certService;

    // Controllers
    AdminController adminController;
    StudentController studentController;

    // State
    // bool isAuthenticated;
    // bool isAdmin;

   public:
    SppApplication();

    void initialize();
    void run();
    void showLoginMenu();
};
