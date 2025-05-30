#include <models/payment.hpp>
#include <string>
#include <sstream>

Payment::Payment(const std::string& id,
                 int studentId,
                 double amount,
                 time_t timestamp,
                 time_t deadline,
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
int Payment::getMonth() const {
    if (timestamp == 0) return 0;
    tm* timeinfo = localtime(&timestamp);
    return timeinfo->tm_mon + 1;  // Months are 0-11 in tm struct
}

int Payment::getYear() const {
    if (timestamp == 0) return 0;
    tm* timeinfo = localtime(&timestamp);
    return timeinfo->tm_year + 1900;  // Years since 1900
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

// HTML representation for Qt display
std::string Payment::toHtml() const {
    std::ostringstream oss;
    oss << "<pre>";
    oss << "ID Pembayaran: " << id << "\n";
    oss << "Jumlah: " << UI::display_currency(amount) << "\n";
    oss << "Timestamp: " << ctime(&timestamp);
    oss << "Deadline: " << ctime(&deadline);
    std::string color = isPaid ? "green" : "red";
    oss << "<span style=\"color:" << color << "\">";
    oss << "Sudah dibayar? " << (isPaid ? "Paid" : "Unpaid") << "</span>";
    oss << "</pre>";
    return oss.str();
}