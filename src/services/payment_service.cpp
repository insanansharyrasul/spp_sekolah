#include  <services/payment_service.hpp>
#include <iostream>

// Helper method to generate a unique payment ID
std::string PaymentService::generatePaymentId(int studentId) {
    std::string id = "PAY" + std::to_string(studentId) + std::to_string(time(0));
    return id;
}

// Constructor
PaymentService::PaymentService(PaymentRepository& paymentRepo, StudentRepository& studentRepo)
    : paymentRepo(paymentRepo), studentRepo(studentRepo) {}

// Business operations
bool PaymentService::setPayment(int studentId, double amount, time_t deadline) {
    std::string id = generatePaymentId(studentId); 
    Payment payment(id, studentId, amount, deadline);
    return paymentRepo.add(payment);
}

bool PaymentService::verifyPaymentStatus(int studentId, int year, int month) {
    std::vector<Payment> payments = paymentRepo.findPaymentsByMonth(year, month);
    for (const auto& payment : payments) {
        if (payment.getStudentId() == studentId && payment.getIsPaid()) {
            return true;
        }
    }
    return false;
}

std::vector<Payment> PaymentService::getStudentPaymentHistory(int studentId) {
    return paymentRepo.findByStudentId(studentId);
}

// Reporting functionality

double PaymentService::calculateTotalPayments(int year, int month) {
    double total = 0.0;
    std::vector<Payment> payments = paymentRepo.findPaymentsByMonth(year, month);
    for (const auto& payment : payments) {
        total += payment.getAmount();
    }
    return total;
}

std::vector<Payment> PaymentService::getOverduePayments() {
    return paymentRepo.findOverduePayments();
}

std::vector<Payment> PaymentService::getAllPayments() {
    return paymentRepo.findAll();
}