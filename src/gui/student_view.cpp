#include "gui/student_view.hpp"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QDate>
#include <QDateTime>
#include <QLocale>
#include <sstream>
#include <models/payment.hpp>
#include <models/question.hpp>
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
    tabWidget->addTab(qnaTab, "Q&A");
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
        // Display HTML-formatted payment
        QString html = QString::fromStdString(payments[0].toHtml());
        paymentDisplay->setHtml(html);
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
            paymentDisplay->clear();
            paymentDisplay->setHtml(QString("<i>No payments found for %1/%2</i>").arg(month).arg(year));
            return;
        }
        // Build combined HTML
        std::ostringstream oss;
        for (const auto &p : filtered) {
            oss << p.toHtml() << "<hr>";
        }
        paymentDisplay->setHtml(QString::fromStdString(oss.str()));
    });
}

void StudentView::setupCertificateTab() {
    QVBoxLayout *certLayout = new QVBoxLayout(certTab);
    // Input row: certificate ID and button
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(new QLabel("Certificate ID:"));
    certIdLineEdit = new QLineEdit();
    inputLayout->addWidget(certIdLineEdit);
    viewCertBtn = new QPushButton("View Certificate");
    inputLayout->addWidget(viewCertBtn);
    certLayout->addLayout(inputLayout);

    // Display area
    certDisplay = new QTextEdit();
    certDisplay->setReadOnly(true);
    certLayout->addWidget(certDisplay);

    connect(viewCertBtn, &QPushButton::clicked, [this]() {
        QString certId = certIdLineEdit->text();
        if (certId.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a certificate ID!");
            return;
        }
        // Fetch formatted certificate details
        std::string details = studentController.getCertificateDetails(currentStudentId, certId.toStdString());
        if (details.empty()) {
            certDisplay->clear();
            certDisplay->setHtml("<i>Certificate invalid or not found.</i>");
        } else {
            certDisplay->setHtml(QString::fromStdString(details));
        }
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
    
    // Answered questions section
    showAnsweredBtn = new QPushButton("Show Answered Questions");
    answeredDisplay = new QTextEdit();
    answeredDisplay->setReadOnly(true);
    qnaLayout->addWidget(showAnsweredBtn);
    qnaLayout->addWidget(answeredDisplay);
    connect(showAnsweredBtn, &QPushButton::clicked, [this]() {
        auto questions = studentController.getAnsweredQuestions(currentStudentId);
        if (questions.empty()) {
            QMessageBox::information(this, "Information", "No answered questions found.");
            answeredDisplay->setHtml("<i>No answered questions found.</i>");
            return;
        }
        std::ostringstream oss;
        for (const auto &q : questions) {
            // format timestamp
            std::time_t ts = q.getTimestamp();
            QString tstr = QLocale().toString(QDateTime::fromSecsSinceEpoch(ts), QLocale::ShortFormat);
            oss << "<b>ID:</b> " << q.getId() << "<br>";
            oss << "<b>Date:</b> " << tstr.toStdString() << "<br>";
            oss << "<span style=\"color:cyan\"><b>Q:</b> " << q.getQuestionText() << "</span><br>";
            oss << "<span style=\"color:green\"><b>A:</b> " << q.getAnswer() << "</span><hr>";
        }
        answeredDisplay->setHtml(QString::fromStdString(oss.str()));
    });
}