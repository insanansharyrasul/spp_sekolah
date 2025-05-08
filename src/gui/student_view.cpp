#include "gui/student_view.hpp"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QDate>
#include <sstream>
#include <models/payment.hpp>
#include <vector>

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
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(new QLabel("Month:"));
    monthSpinBox = new QSpinBox();
    monthSpinBox->setRange(1, 12);
    controlsLayout->addWidget(monthSpinBox);

    controlsLayout->addWidget(new QLabel("Year:"));
    yearSpinBox = new QSpinBox();
    yearSpinBox->setRange(2000, 2100);
    yearSpinBox->setValue(QDate::currentDate().year());
    controlsLayout->addWidget(yearSpinBox);

    showLatestBtn = new QPushButton("Show Latest Payment");
    controlsLayout->addWidget(showLatestBtn);

    showByDateBtn = new QPushButton("Show Payment by Month/Year");
    controlsLayout->addWidget(showByDateBtn);

    paymentLayout->addLayout(controlsLayout);

    paymentDisplay = new QTextEdit();
    paymentDisplay->setReadOnly(true);
    paymentLayout->addWidget(paymentDisplay);

    connect(showLatestBtn, &QPushButton::clicked, [this]() {
        auto payments = studentController.getPaymentHistory(currentStudentId);
        if (payments.empty()) {
            QMessageBox::information(this, "Information", "No payments found.");
            return;
        }
        std::stringstream ss;
        ss << payments[0];
        paymentDisplay->setPlainText(QString::fromStdString(ss.str()));
    });

    connect(showByDateBtn, &QPushButton::clicked, [this]() {
        int month = monthSpinBox->value();
        int year = yearSpinBox->value();
        auto payments = studentController.getPaymentHistory(currentStudentId);
        std::vector<Payment> filtered;
        for (const auto &p : payments) {
            if (p.getMonth() == month && p.getYear() == year) {
                filtered.push_back(p);
            }
        }
        if (filtered.empty()) {
            paymentDisplay->setPlainText(QString("No payments found for %1/%2").arg(month).arg(year));
            return;
        }
        std::stringstream ss;
        for (const auto &p : filtered) {
            ss << p << "\n----------------\n";
        }
        paymentDisplay->setPlainText(QString::fromStdString(ss.str()));
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