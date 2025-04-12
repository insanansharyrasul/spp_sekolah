#pragma once
#include <ctime>
#include <string>
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
            time_t deadline = 0,
            bool isPaid = false);

    // Getter
    std::string getId() const;
    int getStudentId() const;
    double getAmount() const;
    time_t getTimestamp() const;
    time_t getDeadline() const;
    bool getIsPaid() const;

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
};