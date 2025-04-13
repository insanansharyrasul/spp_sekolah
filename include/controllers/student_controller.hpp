#include <services/payment_service.hpp>
#include <services/student_service.hpp>
class StudentController {
   private:
    StudentService& studentService;
    PaymentService& paymentService;

   public:
    StudentController(StudentService& studentService, PaymentService& paymentService);

    // UI handling methods
    void showDashboard(int studentId);
    void viewProfile(int studentId);
    void viewPayments(int studentId);
};