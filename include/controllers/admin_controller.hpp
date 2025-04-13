#pragma once
#include <repositories/student_repository.hpp>
#include <services/certificate_service.hpp>
#include <services/payment_service.hpp>
#include <services/student_service.hpp>
class AdminController {
   private:
    StudentService& studentService;
    PaymentService& paymentService;
    CertificateService& certService;

   public:
    AdminController(StudentService& studentService,
                    PaymentService& paymentService,
                    CertificateService& certService
                   );

    // UI handling methods
    void showDashboard();
    void registerNewStudent();
    void viewAllStudents();
    void viewAllPayments();
    void setPayment();
    void makeCertificate();
};