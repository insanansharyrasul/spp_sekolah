#pragma once
#include <ctime>
#include <iomanip>
#include <string>
#include <utils/ui_helpers.hpp>
// The constructor is must be in id, studentId, amount, timestamp, deadline, isPaid order
class Payment {
   private:
    std::string id;
    int studentId;
    double amount;
    time_t timestamp;
    time_t deadline;
    bool isPaid;

   public:
    Payment(const std::string& id = 0,
            int studentId = 0,
            double amount = 0,
            time_t timestamp = 0,
            time_t deadline = 0,
            bool isPaid = false);

    // Getter
    std::string getId() const;
    int getStudentId() const;
    double getAmount() const;
    time_t getTimestamp() const;
    time_t getDeadline() const;
    bool getIsPaid() const;
    int getMonth() const;
    int getYear() const;

    // Setter
    void setId(const std::string& id);
    void setStudentId(int studentId);
    void setAmount(double amount);
    void setTimestamp(time_t timestamp);
    void setDeadline(time_t deadline);
    void setIsPaid(bool isPaid);
    void setIsPaid();
    void setIsUnpaid();

    // Method
    bool isOverdue() const;
    int daysRemaining() const;

    friend std::ostream& operator<<(std::ostream& os, const Payment& payment) {
        std::string statusText = payment.isPaid ? "Paid" : "Unpaid";
        std::string statusColor = payment.isPaid ? UI::Color::GREEN : UI::Color::RED;
        time_t timestamp = payment.timestamp;
        time_t deadline = payment.deadline;
        os << std::setw(20) << std::left << "ID Pembayaran: " << payment.id << "\n"
           << std::setw(20) << std::left << "Jumlah: " << UI::display_currency(payment.amount) << "\n"
           << std::setw(20) << std::left << "Timestamp: " << ctime(&timestamp)
           << std::setw(20) << std::left << "Deadline: " << ctime(&deadline)
           << std::setw(20) << std::left << "Sudah dibayar? " << statusColor << statusText << UI::Color::RESET;
        ;
        return os;
    }
};