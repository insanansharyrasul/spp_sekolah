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

    bool isOverdue() const {
        return deadline > 0 && time(0) > deadline;
    }

    int daysRemaining() const {
        if (deadline == 0) return 0;
        return (deadline - time(0)) / 86400;
    }
};