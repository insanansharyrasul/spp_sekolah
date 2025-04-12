#include <repositories/payment_repository.hpp>
#include <fstream>
#include <sstream>

PaymentRepository::PaymentRepository(const std::string& filePath) : dataFilePath(filePath) {
    loadFromFile();
}

// CRUD operations
bool PaymentRepository::add(const Payment& payment) {
    if (payments.find(payment.getId()) != payments.end()) {
        return false;  
    }
    payments[payment.getId()] = payment;
    studentPaymentIndex.insert({payment.getStudentId(), payment.getId()});
    return saveToFile();
};

Payment* PaymentRepository::findById(const std::string& id) {
    auto it = payments.find(id);
    if (it != payments.end()) {
        return &it->second;
    }
    return nullptr;  
};

std::vector<Payment> PaymentRepository::findByStudentId(int studentId) {
    std::vector<Payment> result;
    auto range = studentPaymentIndex.equal_range(studentId);
    for (auto it = range.first; it != range.second; ++it) {
        result.push_back(payments[it->second]);
    }
    return result;
};

std::vector<Payment> PaymentRepository::findAll() {
    std::vector<Payment> result;
    for (const auto& pair : payments) {
        result.push_back(pair.second);
    }
    return result;
};

// Specialized queries
std::vector<Payment> PaymentRepository::findOverduePayments() {
    std::vector<Payment> result;
    time_t now = time(0);
    for (const auto& pair : payments) {
        const Payment& payment = pair.second;
        if (!payment.getIsPaid() && payment.getDeadline() < now) {
            result.push_back(payment);
        }
    }
    return result;
};
std::vector<Payment> PaymentRepository::findPaymentsByMonth(int year, int month) {
    std::vector<Payment> result;
    for (const auto& pair : payments) {
        const Payment& payment = pair.second;
        time_t timestamp = payment.getTimestamp();
        struct tm* timeinfo = localtime(&timestamp);
        if (timeinfo->tm_year + 1900 == year && timeinfo->tm_mon + 1 == month) {
            result.push_back(payment);
        }
    }
    return result;

};

// Persistence
bool PaymentRepository::loadFromFile() {
    std::ifstream inFile(dataFilePath);
    if (!inFile.is_open()) {
        return false;  // Failed to open file
    }

    payments.clear();
    studentPaymentIndex.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string id;
        int studentId;
        double amount;
        time_t deadline;

        ss >> id;
        ss.ignore();  
        ss >> studentId;
        ss.ignore();  
        ss >> amount;
        ss.ignore();  
        ss >> deadline;

        Payment payment(id, studentId, amount);
        payment.setDeadline(deadline);
        payments[id] = payment;
        studentPaymentIndex.insert({studentId, id});
    }
    inFile.close();
    return true;
};

bool PaymentRepository::saveToFile() {
    std::ofstream outFile(dataFilePath);
    if (!outFile.is_open()) {
        return false;  // Failed to open file
    }

    for (const auto& pair : payments) {
        const Payment& payment = pair.second;
        outFile << payment.getId() << ","
                << payment.getStudentId() << ","
                << payment.getAmount() << ","
                << payment.getDeadline() << "\n";
    }
    outFile.close();
    return true;

};