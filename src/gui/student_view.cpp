#include "gui/student_view.hpp"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>

StudentView::StudentView(StudentController& controller, QWidget *parent) 
    : QWidget(parent), studentController(controller), currentStudentId(-1) {
    
    tabWidget = new QTabWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
    
    infoTab = new QWidget();
    paymentTab = new QWidget();
    certTab = new QWidget();
    qnaTab = new QWidget();
}

StudentView::~StudentView() {}

void StudentView::setupDashboard(int studentId) {
    currentStudentId = studentId;
    
    tabWidget->clear();
    
    Student* student = studentController.getStudentService().getStudentById(studentId);
    
    if (!student) {
        QMessageBox::critical(this, "Error", "Student data not found!");
        return;
    }
    
    setupInfoTab(student);
    setupPaymentTab();
    setupCertificateTab();
    setupQnaTab();
    
    tabWidget->addTab(infoTab, "My Information");
    tabWidget->addTab(paymentTab, "My Payments");
    tabWidget->addTab(certTab, "My Certificates");
    tabWidget->addTab(qnaTab, "Ask a Question");
}

void StudentView::setupInfoTab(Student* student) {
    QVBoxLayout *infoLayout = new QVBoxLayout(infoTab);
    
    QGroupBox *infoBox = new QGroupBox("Student Information");
    QGridLayout *infoBoxLayout = new QGridLayout(infoBox);
    
    infoBoxLayout->addWidget(new QLabel("ID:"), 0, 0);
    infoBoxLayout->addWidget(new QLabel(QString::number(student->getId())), 0, 1);
    
    infoBoxLayout->addWidget(new QLabel("Name:"), 1, 0);
    infoBoxLayout->addWidget(new QLabel(QString::fromStdString(student->getName())), 1, 1);
    
    infoBoxLayout->addWidget(new QLabel("Year Registered:"), 2, 0);
    infoBoxLayout->addWidget(new QLabel(QString::number(student->getYearRegistered())), 2, 1);
    
    infoBoxLayout->addWidget(new QLabel("Class ID:"), 3, 0);
    infoBoxLayout->addWidget(new QLabel(QString::number(student->getClassId())), 3, 1);
    
    infoLayout->addWidget(infoBox);
}

void StudentView::setupPaymentTab() {
    QVBoxLayout *paymentLayout = new QVBoxLayout(paymentTab);
    
    QPushButton *viewPaymentsBtn = new QPushButton("View My Payments");
    paymentLayout->addWidget(viewPaymentsBtn);
    
    connect(viewPaymentsBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "Information", "View Payments functionality to be implemented");
    });
}

void StudentView::setupCertificateTab() {
    QVBoxLayout *certLayout = new QVBoxLayout(certTab);
    
    QPushButton *viewCertBtn = new QPushButton("View My Certificates");
    certLayout->addWidget(viewCertBtn);
    
    connect(viewCertBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "Information", "View Certificate functionality to be implemented");
    });
}

void StudentView::setupQnaTab() {
    QVBoxLayout *qnaLayout = new QVBoxLayout(qnaTab);
    
    QPushButton *askQuestionBtn = new QPushButton("Submit a New Question");
    questionEdit = new QTextEdit();
    
    qnaLayout->addWidget(new QLabel("Your Question:"));
    qnaLayout->addWidget(questionEdit);
    qnaLayout->addWidget(askQuestionBtn);
    
    connect(askQuestionBtn, &QPushButton::clicked, [this]() {
        QString question = questionEdit->toPlainText();
        if (question.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a question!");
            return;
        }
        
        bool success = studentController.submitQuestion(currentStudentId, question.toStdString());
        
        if (success) {
            QMessageBox::information(this, "Success", "Your question has been submitted!");
            questionEdit->clear();
        } else {
            QMessageBox::critical(this, "Error", "Failed to submit question. Try again later.");
        }
    });
}