#include "gui/admin_view.hpp"

#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

AdminView::AdminView(AdminController& controller, QWidget *parent) 
    : QWidget(parent), adminController(controller) {
    
    tabWidget = new QTabWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
    
    studentTab = new QWidget();
    paymentTab = new QWidget();
    certTab = new QWidget();
    qnaTab = new QWidget();
}

AdminView::~AdminView() {}

void AdminView::setupDashboard() {
    tabWidget->clear();
    
    setupStudentTab();
    setupPaymentTab();
    setupCertificateTab();
    setupQnaTab();
    
    tabWidget->addTab(studentTab, "Student Management");
    tabWidget->addTab(paymentTab, "Payment Management");
    tabWidget->addTab(certTab, "Certificate Management");
    tabWidget->addTab(qnaTab, "Questions & Answers");
}

void AdminView::setupStudentTab() {
    QVBoxLayout *studentLayout = new QVBoxLayout(studentTab);
    
    QPushButton *viewStudentsBtn = new QPushButton("View All Students");
    QPushButton *registerStudentBtn = new QPushButton("Register New Student");
    
    studentLayout->addWidget(viewStudentsBtn);
    studentLayout->addWidget(registerStudentBtn);
    
    connect(viewStudentsBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "Information", "View Students functionality to be implemented");
    });
    
    connect(registerStudentBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "Information", "Register Student functionality to be implemented");
    });
}

void AdminView::setupPaymentTab() {
    QVBoxLayout *paymentLayout = new QVBoxLayout(paymentTab);
    
    QPushButton *viewPaymentsBtn = new QPushButton("View All Payments");
    QPushButton *setPaymentBtn = new QPushButton("Set New Payment");
    
    paymentLayout->addWidget(viewPaymentsBtn);
    paymentLayout->addWidget(setPaymentBtn);
    
    // Connect button signals
    connect(viewPaymentsBtn, &QPushButton::clicked, [this]() {
        // Implement view payments functionality using adminController
        QMessageBox::information(this, "Information", "View Payments functionality to be implemented");
    });
    
    connect(setPaymentBtn, &QPushButton::clicked, [this]() {
        // Implement set payment functionality using adminController
        QMessageBox::information(this, "Information", "Set Payment functionality to be implemented");
    });
}

void AdminView::setupCertificateTab() {
    QVBoxLayout *certLayout = new QVBoxLayout(certTab);
    
    QPushButton *makeCertBtn = new QPushButton("Generate Certificate");
    certLayout->addWidget(makeCertBtn);
    
    // Connect button signals
    connect(makeCertBtn, &QPushButton::clicked, [this]() {
        // Implement certificate generation functionality using adminController
        QMessageBox::information(this, "Information", "Generate Certificate functionality to be implemented");
    });
}

void AdminView::setupQnaTab() {
    QVBoxLayout *qnaLayout = new QVBoxLayout(qnaTab);
    
    QPushButton *answerQuestionsBtn = new QPushButton("Answer Student Questions");
    qnaLayout->addWidget(answerQuestionsBtn);
    
    // Connect button signals
    connect(answerQuestionsBtn, &QPushButton::clicked, [this]() {
        // Implement answer questions functionality using adminController
        QMessageBox::information(this, "Information", "Answer Questions functionality to be implemented");
    });
}