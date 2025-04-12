#include <payment_service.hpp>
#include <student_repository.hpp>
class StudentController {
   private:
    StudentRepository& studentRepo;
    // PaymentService& paymentService;

   public:
    StudentController(StudentRepository& repo
                      //  PaymentService& service
    );

    // UI handling methods
    void showDashboard(int studentId);
    void viewProfile(int studentId);
    void viewPayments(int studentId);
};