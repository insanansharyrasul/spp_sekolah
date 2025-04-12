#pragma once
#include <repositories/payment_repository.hpp>
#include <repositories/student_repository.hpp>
#include <models/payment.hpp>
#include <string>
#include <vector>

class PaymentService {
   private:
    PaymentRepository& paymentRepo;
    StudentRepository& studentRepo;

    // Helper methods for generating IDs, validating data, etc.
    std::string generatePaymentId(int studentId);

   public:
    PaymentService(PaymentRepository& paymentRepo, StudentRepository& studentRepo);

    // Business operations
    bool processPayment(int studentId, double amount, time_t deadline);
    bool verifyPaymentStatus(int studentId, int year, int month);
    std::vector<Payment> getStudentPaymentHistory(int studentId);

    // Reporting functionality
    double calculateTotalPayments(int year, int month);
    std::vector<Payment> getOverduePayments();
    std::vector<Payment> getAllPayments();
};