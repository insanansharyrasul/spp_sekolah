#pragma once
#include <data_structures/SimpleStack.hpp>
#include <functional>
#include <repositories/student_repository.hpp>
#include <services/certificate_service.hpp>
#include <services/payment_service.hpp>
#include <services/qna_service.hpp>
#include <services/student_service.hpp>
#include <string>

// Action class to represent operations that can be undone
class AdminAction {
   public:
    enum ActionType {
        REGISTER_STUDENT,
        PROCESS_PAYMENT,
        GENERATE_CERTIFICATE
    };

    AdminAction(ActionType type,
                const std::string& id,
                std::function<bool()> undoFunction)
        : type(type),
          id(id),
          undoFunction(undoFunction) {}

    ActionType getType() const { return type; }
    std::string getId() const { return id; }
    bool undo() { return undoFunction(); }

    std::string getActionName() const {
        switch (type) {
            case REGISTER_STUDENT:
                return "Student Registration";
            case PROCESS_PAYMENT:
                return "Payment Processing";
            case GENERATE_CERTIFICATE:
                return "Certificate Generation";
            default:
                return "Unknown Action";
        }
    }

   private:
    ActionType type;
    std::string id;  // ID of the affected entity (student ID, payment ID, etc.)
    std::function<bool()> undoFunction;
};

class AdminController {
   private:
    StudentService& studentService;
    PaymentService& paymentService;
    CertificateService& certService;
    QnAService& qnaService;
    SimpleStack<AdminAction> actionStack;  // Stack for undo operations

   public:
    AdminController(StudentService& studentService,
                    PaymentService& paymentService,
                    CertificateService& certService,
                    QnAService& qnaService);

    // UI handling methods
    void showDashboard();
    void registerNewStudent();
    void viewAllStudents();
    void viewAllPayments();
    void setPayment();
    void makeCertificate();
    void undoLastAction();  // New method for undoing actions

    // QnA methods
    void answerQuestions();

    // Service
    StudentService& getStudentService();
};