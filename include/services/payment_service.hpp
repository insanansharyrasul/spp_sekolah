#pragma once
#include <models/payment.hpp>
#include <repositories/payment_repository.hpp>
#include <repositories/student_repository.hpp>
#include <string>
#include <vector>

// Forward declaration
class CertificateService;

class PaymentService {
   private:
    PaymentRepository& paymentRepo;
    StudentRepository& studentRepo;

    // Helper methods for generating IDs, validating data, etc.
    std::string generatePaymentId(int studentId);

   public:
    PaymentService(PaymentRepository& paymentRepo, StudentRepository& studentRepo);

    // Business operations
    std::string setPayment(int studentId, double amount, time_t deadline);
    bool verifyPaymentStatus(int studentId, int year, int month);
    std::vector<Payment> getStudentPaymentHistory(int studentId);
    bool deletePayment(const std::string& paymentId);
    bool verifyCertificate(const std::string& certId, int studentId, CertificateService& certService);

    // Reporting functionality
    double calculateTotalPayments(int year, int month);
    std::vector<Payment> getOverduePayments();
    std::vector<Payment> getAllPayments();
};