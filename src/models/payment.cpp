#include <models/payment.hpp>
#include <string>

Payment::Payment(const std::string& id,
                 int studentId,
                 double amount,
                 time_t deadline,
                 time_t timestamp,
                 bool isPaid) : id(id),
                                studentId(studentId),
                                amount(amount),
                                deadline(deadline),
                                timestamp(timestamp),
                                isPaid(isPaid) {};

// Getter
std::string Payment::getId() const {
    return id;
}
int Payment::getStudentId() const {
    return studentId;
}
double Payment::getAmount() const {
    return amount;
}
time_t Payment::getTimestamp() const {
    return timestamp;
}
time_t Payment::getDeadline() const {
    return deadline;
}
bool Payment::getIsPaid() const {
    return isPaid;
}

// Setter
void Payment::setId(const std::string& id) {
    this->id = id;
}
void Payment::setStudentId(int studentId) {
    this->studentId = studentId;
}
void Payment::setAmount(double amount) {
    this->amount = amount;
}
void Payment::setTimestamp(time_t timestamp) {
    this->timestamp = timestamp;
}
void Payment::setDeadline(time_t deadline) {
    this->deadline = deadline;
}
void Payment::setIsPaid(bool isPaid) {
    this->isPaid = isPaid;
}
void Payment::setIsPaid() {
    this->isPaid = true;
}
void Payment::setIsUnpaid() {
    this->isPaid = false;
}

bool Payment::isOverdue() const {
    return deadline > 0 && time(0) > deadline;
}

int Payment::daysRemaining() const {
    if (deadline == 0) return 0;
    return (deadline - time(0)) / 86400;
}