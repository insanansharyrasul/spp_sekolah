// #include <services/payment_service.hpp>
// #include <ctime>
// #include <sstream>
// #include <iomanip>

// PaymentService::PaymentService(PaymentRepository& paymentRepo, StudentRepository& studentRepo)
//     : paymentRepo(paymentRepo), studentRepo(studentRepo) {}

// bool PaymentService::processPayment(int studentId, double amount, time_t deadline) {
//     // Validate student ID
//     Student* student = studentRepo.findById(studentId);
//     if (!student) {
//         return false;  // Student not found
//     }

//     // Generate a unique payment ID
//     std::string paymentId = generatePaymentId(studentId);

//     // Create a new payment object
//     Payment newPayment(paymentId, studentId, amount, time(0), deadline);

//     // Save the payment to the repository
//     return paymentRepo.add(newPayment);
// }

// bool PaymentService::verifyPaymentStatus(int studentId, int year, int month) {
//     // Check if the payment exists for the given student and date
//     std::vector<Payment> payments = paymentRepo.findByStudentId(studentId);
//     for (const auto& payment : payments) {
//         time_t timestamp = payment.getTimestamp();
//         struct tm* timeInfo = localtime(&timestamp);
        
//         if ((timeInfo->tm_year + 1900) == year && (timeInfo->tm_mon + 1) == month) {
//             return true;  // Payment found
//         }
//     }
//     return false;  // Payment not found
// }

// std::vector<Payment> PaymentService::getStudentPaymentHistory(int studentId) {
//     return paymentRepo.findByStudentId(studentId);
// }

// std::vector<Payment> PaymentService::getAllPayments() {
//     return paymentRepo.findAll();
// }

// std::vector<Payment> PaymentService::getOverduePayments() {
//     std::vector<Payment> overduePayments;
//     std::vector<Payment> allPayments = paymentRepo.findAll();
    
//     time_t now = time(0);
//     for (const auto& payment : allPayments) {
//         if (payment.getDeadline() < now) {
//             overduePayments.push_back(payment);
//         }
//     }
    
//     return overduePayments;
// }

// double PaymentService::calculateTotalPayments(int year, int month) {
//     double total = 0.0;
//     std::vector<Payment> allPayments = paymentRepo.findAll();
    
//     for (const auto& payment : allPayments) {
//         time_t timestamp = payment.getTimestamp();
//         struct tm* timeInfo = localtime(&timestamp);
        
//         if ((timeInfo->tm_year + 1900) == year && (timeInfo->tm_mon + 1) == month) {
//             total += payment.getAmount();
//         }
//     }
    
//     return total;
// }

// // Private helper methods

// std::string PaymentService::generatePaymentId(int studentId) {
//     // Format: YYYYMM-STUDENTID-TIMESTAMP
//     time_t now = time(0);
//     struct tm* timeInfo = localtime(&now);
    
//     std::stringstream ss;
//     ss << std::setfill('0') 
//        << (timeInfo->tm_year + 1900)
//        << std::setw(2) << (timeInfo->tm_mon + 1)
//        << "-"
//        << studentId
//        << "-"
//        << now;
       
//     return ss.str();
// }