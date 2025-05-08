#include <iostream>
#include <services/certificate_service.hpp>
#include <services/payment_service.hpp>
#include <sstream>

// Helper method to generate a unique payment ID
std::string PaymentService::generatePaymentId(int studentId) {
    std::string id = "PAY" + std::to_string(studentId) + std::to_string(time(0));
    return id;
}

// Constructor
PaymentService::PaymentService(PaymentRepository& paymentRepo, StudentRepository& studentRepo)
    : paymentRepo(paymentRepo), studentRepo(studentRepo) {}

// Business operations
std::string PaymentService::setPayment(int studentId, double amount, time_t deadline) {
    std::string id = generatePaymentId(studentId);
    time_t timestamp = time(0);
    Payment payment(id, studentId, amount, timestamp, deadline, false);
    if (paymentRepo.add(payment)) {
        return id;
    }
    return "";  // Empty string indicates failure
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

bool PaymentService::deletePayment(const std::string& paymentId) {
    Payment* payment = paymentRepo.findById(paymentId);
    if (!payment) {
        return false;
    }

    paymentRepo.remove(paymentId);
    return true;
}

bool PaymentService::verifyCertificate(const std::string& certId, int studentId, CertificateService& certService) {
    if (certId.empty()) {
        return false;
    }

    try {
        size_t certificateHash = std::stoull(certId);
        std::string decodedData = certService.decodeCertificate(certificateHash);

        if (decodedData.empty()) {
            return false;  // Certificate not found or invalid
        }

        // Parse the decoded data (format: paymentId,studentId,amount,deadline)
        std::istringstream ss(decodedData);
        std::string paymentId;
        std::string studentIdStr;
        std::string amountStr;
        std::string deadlineStr;

        std::getline(ss, paymentId, ',');
        std::getline(ss, studentIdStr, ',');
        std::getline(ss, amountStr, ',');
        std::getline(ss, deadlineStr, ',');

        int certStudentId = std::stoi(studentIdStr);

        // Verify this certificate belongs to the requesting student
        if (certStudentId != studentId) {
            return false;
        }

        return true;
    } catch (const std::exception& e) {
        // Handle conversion errors or other exceptions
        return false;
    }
}