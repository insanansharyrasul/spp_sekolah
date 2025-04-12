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
    Payment(const std::string& id, int studentId, double amount);

    bool isOverdue() const;
    int daysRemaining() const;
};