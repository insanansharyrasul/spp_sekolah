#include "gui/admin_view.hpp"

#include <QDateTime>
#include <QHeaderView>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <qtextedit.h>

AdminView::AdminView(AdminController &controller, QWidget *parent)
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

    QTableWidget *studentTable = new QTableWidget();
    studentTable->setSortingEnabled(true);
    studentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    studentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    studentTable->setAlternatingRowColors(true);

    QStringList headers = {"ID", "Name", "Year Registered", "Class ID"};
    studentTable->setColumnCount(headers.size());
    studentTable->setHorizontalHeaderLabels(headers);
    studentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton *viewStudentsBtn = new QPushButton("View All Students");
    QPushButton *reloadStudentsBtn = new QPushButton("Reload Data");
    QPushButton *registerStudentBtn = new QPushButton("Register New Student");

    studentLayout->addWidget(studentTable);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(viewStudentsBtn);
    buttonLayout->addWidget(reloadStudentsBtn);
    studentLayout->addLayout(buttonLayout);
    
    studentLayout->addWidget(registerStudentBtn);

    auto loadStudentData = [this, studentTable]() {
        studentTable->clearContents();
        studentTable->setRowCount(0);
        studentTable->setSortingEnabled(false); 
        
        std::vector<Student> studentList = adminController.getStudentService().getAllStudents();

        if (studentList.empty()) {
            QMessageBox::information(this, "Information", "No students found.");
            return;
        }

        studentTable->setRowCount(studentList.size());
        int row = 0;

        for (const auto &student : studentList) {
            QTableWidgetItem *idItem = new QTableWidgetItem();
            idItem->setData(Qt::DisplayRole, student.getId());

            QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(student.getName()));

            QTableWidgetItem *yearItem = new QTableWidgetItem();
            yearItem->setData(Qt::DisplayRole, student.getYearRegistered());

            QTableWidgetItem *classItem = new QTableWidgetItem();
            classItem->setData(Qt::DisplayRole, student.getClassId());

            studentTable->setItem(row, 0, idItem);
            studentTable->setItem(row, 1, nameItem);
            studentTable->setItem(row, 2, yearItem);
            studentTable->setItem(row, 3, classItem);

            row++;
        }

        studentTable->setSortingEnabled(true);
        studentTable->sortByColumn(0, Qt::AscendingOrder);
    };

    connect(viewStudentsBtn, &QPushButton::clicked, loadStudentData);
    connect(reloadStudentsBtn, &QPushButton::clicked, loadStudentData);

    connect(registerStudentBtn, &QPushButton::clicked, [this, studentTable, loadStudentData]() {
        bool ok;
        QString name = QInputDialog::getText(this,
                              "Register New Student",
                              "Student Name:",
                              QLineEdit::Normal,
                              QString(),
                              &ok);
        if (!ok || name.trimmed().isEmpty()) return;
        int year = QInputDialog::getInt(this,
                            "Register New Student",
                            "Year Enrolled:",
                            QDate::currentDate().year(),
                            1900, QDate::currentDate().year(),
                            1, &ok);
        if (!ok) return;
        int classId = QInputDialog::getInt(this,
                             "Register New Student",
                             "Class ID:",
                             1,
                             1, 9999,
                             1, &ok);
        if (!ok) return;
        std::string newId = adminController.createStudent(name.toStdString(), year, classId);
        if (!newId.empty()) {
            QMessageBox::information(this,
                "Success",
                QString("Student registered with ID: %1").arg(QString::fromStdString(newId)));
            // Refresh table with the lambda function
            loadStudentData();
        } else {
            QMessageBox::critical(this,
                "Error",
                "Failed to register student. Please try again.");
        }
     });
}

void AdminView::setupPaymentTab() {
    QVBoxLayout *paymentLayout = new QVBoxLayout(paymentTab);
    
    // Create table widget for payments
    QTableWidget *paymentTable = new QTableWidget();
    paymentTable->setSortingEnabled(true);
    paymentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    paymentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    paymentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    paymentTable->setAlternatingRowColors(true);
    
    QStringList headers = {"ID", "Student ID", "Amount", "Timestamp", "Deadline", "Status"};
    paymentTable->setColumnCount(headers.size());
    paymentTable->setHorizontalHeaderLabels(headers);
    paymentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    QPushButton *viewPaymentsBtn = new QPushButton("View All Payments");
    QPushButton *setPaymentBtn = new QPushButton("Set New Payment");
    QPushButton *markPaidBtn = new QPushButton("Mark as Paid");
    
    paymentLayout->addWidget(paymentTable);
    paymentLayout->addWidget(viewPaymentsBtn);
    paymentLayout->addWidget(setPaymentBtn);
    paymentLayout->addWidget(markPaidBtn);

    // Load payments data into the table
    connect(viewPaymentsBtn, &QPushButton::clicked, [this, paymentTable]() {
        paymentTable->clearContents();
        paymentTable->setRowCount(0);
        paymentTable->setSortingEnabled(false);
        
        std::vector<Payment> paymentList = adminController.getPaymentService().getAllPayments();
        
        if (paymentList.empty()) {
            QMessageBox::information(this, "Information", "No payments found.");
            return;
        }
        
        paymentTable->setRowCount(paymentList.size());
        int row = 0;
        
        for (const auto &payment : paymentList) {
            // Payment ID
            QTableWidgetItem *idItem = new QTableWidgetItem(QString::fromStdString(payment.getId()));
            
            // Student ID
            QTableWidgetItem *studentIdItem = new QTableWidgetItem(QString::number(payment.getStudentId()));
            
            // Amount
            QTableWidgetItem *amountItem = new QTableWidgetItem();
            amountItem->setData(Qt::DisplayRole, payment.getAmount());
            amountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            
            // Timestamp
            time_t timestamp = payment.getTimestamp();
            std::string timestamp_str = std::ctime(&timestamp);
            if (!timestamp_str.empty() && timestamp_str.back() == '\n')
                timestamp_str.pop_back();
            QTableWidgetItem *timestampItem = new QTableWidgetItem(QString::fromStdString(timestamp_str));
            
            // Deadline
            time_t deadline = payment.getDeadline();
            std::string deadline_str = std::ctime(&deadline);
            if (!deadline_str.empty() && deadline_str.back() == '\n')
                deadline_str.pop_back();
            QTableWidgetItem *deadlineItem = new QTableWidgetItem(QString::fromStdString(deadline_str));
            
            // Status
            QString status = payment.getIsPaid() ? "Paid" : "Unpaid";
            QTableWidgetItem *statusItem = new QTableWidgetItem(status);
            
            // Set color based on payment status
            if (payment.getIsPaid()) {
                statusItem->setForeground(QBrush(QColor(0, 170, 0))); // Green for paid
            } else {
                statusItem->setForeground(QBrush(QColor(255, 0, 0))); // Red for unpaid
            }
            
            paymentTable->setItem(row, 0, idItem);
            paymentTable->setItem(row, 1, studentIdItem);
            paymentTable->setItem(row, 2, amountItem);
            paymentTable->setItem(row, 3, timestampItem);
            paymentTable->setItem(row, 4, deadlineItem);
            paymentTable->setItem(row, 5, statusItem);
            
            row++;
        }

        paymentTable->setSortingEnabled(true);
        paymentTable->sortByColumn(0, Qt::AscendingOrder);
    });
    
    // Handle set payment button click
    connect(setPaymentBtn, &QPushButton::clicked, [this, paymentTable]() {
        bool ok;
        int studentId = QInputDialog::getInt(this, "Set Payment", "Student ID:", 1, 1, 999999, 1, &ok);
        
        if (!ok) return;
        
        double amount = QInputDialog::getDouble(this, "Set Payment", "Amount:", 0.0, 0.01, 1000000.0, 2, &ok);
        
        if (!ok) return;
        
        // Set deadline to 30 days from now
        time_t deadline = time(0) + (30 * 24) * (60 * 60);
        std::string deadline_str = std::ctime(&deadline);
        if (!deadline_str.empty() && deadline_str.back() == '\n')
            deadline_str.pop_back();
            
        // Show confirmation dialog with deadline information
        QMessageBox msgBox;
        msgBox.setWindowTitle("Confirm Payment Setup");
        msgBox.setText(QString("Setting up payment for:\nStudent ID: %1\nAmount: %2\nDeadline: %3")
                      .arg(studentId)
                      .arg(amount)
                      .arg(QString::fromStdString(deadline_str)));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int ret = msgBox.exec();
        
        if (ret == QMessageBox::Ok) {
            std::string paymentId = adminController.getPaymentService().setPayment(studentId, amount, deadline);
            
            if (!paymentId.empty()) {
                QMessageBox::information(this, "Success", QString("Payment has been set with ID: %1")
                                        .arg(QString::fromStdString(paymentId)));
                
                // Refresh the table to show the new payment
                paymentTable->setRowCount(0);
                std::vector<Payment> paymentList = adminController.getPaymentService().getAllPayments();
                
                if (!paymentList.empty()) {
                    paymentTable->setRowCount(paymentList.size());
                    int row = 0;
                    
                    for (const auto &payment : paymentList) {
                        // Payment ID
                        QTableWidgetItem *idItem = new QTableWidgetItem(QString::fromStdString(payment.getId()));
                        
                        // Student ID
                        QTableWidgetItem *studentIdItem = new QTableWidgetItem(QString::number(payment.getStudentId()));
                        
                        // Amount
                        QTableWidgetItem *amountItem = new QTableWidgetItem();
                        amountItem->setData(Qt::DisplayRole, payment.getAmount());
                        amountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                        
                        // Timestamp
                        time_t timestamp = payment.getTimestamp();
                        std::string timestamp_str = std::ctime(&timestamp);
                        if (!timestamp_str.empty() && timestamp_str.back() == '\n')
                            timestamp_str.pop_back();
                        QTableWidgetItem *timestampItem = new QTableWidgetItem(QString::fromStdString(timestamp_str));
                        
                        // Deadline
                        time_t deadline = payment.getDeadline();
                        std::string deadline_str = std::ctime(&deadline);
                        if (!deadline_str.empty() && deadline_str.back() == '\n')
                            deadline_str.pop_back();
                        QTableWidgetItem *deadlineItem = new QTableWidgetItem(QString::fromStdString(deadline_str));
                        
                        // Status
                        QString status = payment.getIsPaid() ? "Paid" : "Unpaid";
                        QTableWidgetItem *statusItem = new QTableWidgetItem(status);
                        
                        // Set color based on payment status
                        if (payment.getIsPaid()) {
                            statusItem->setForeground(QBrush(QColor(0, 170, 0))); // Green for paid
                        } else {
                            statusItem->setForeground(QBrush(QColor(255, 0, 0))); // Red for unpaid
                        }
                        
                        paymentTable->setItem(row, 0, idItem);
                        paymentTable->setItem(row, 1, studentIdItem);
                        paymentTable->setItem(row, 2, amountItem);
                        paymentTable->setItem(row, 3, timestampItem);
                        paymentTable->setItem(row, 4, deadlineItem);
                        paymentTable->setItem(row, 5, statusItem);
                        
                        row++;
                    }
                    
                    paymentTable->sortByColumn(0, Qt::AscendingOrder);
                }
            } else {
                QMessageBox::critical(this, "Error", "Failed to set payment. Please check if the student ID exists.");
            }
        }
    });
    
    // Handle 'Mark as Paid' button click
    connect(markPaidBtn, &QPushButton::clicked, [this, paymentTable, viewPaymentsBtn]() {
        int row = paymentTable->currentRow();
        if (row < 0) {
            QMessageBox::warning(this, "Warning", "Select a payment first.");
            return;
        }
        QString idStr = paymentTable->item(row, 0)->text();
        bool ok = adminController.getPaymentService().markPaymentPaid(idStr.toStdString());
        if (ok) {
            QMessageBox::information(this, "Success", "Payment marked as paid.");
            viewPaymentsBtn->click();
        } else {
            QMessageBox::critical(this, "Error", "Failed to mark payment as paid.");
        }
    });
}

void AdminView::setupCertificateTab() {
    QVBoxLayout *certLayout = new QVBoxLayout(certTab);

    QPushButton *makeCertBtn = new QPushButton("Generate Certificate");
    certLayout->addWidget(makeCertBtn);

    connect(makeCertBtn, &QPushButton::clicked, [this]() {
        bool ok;
        QString paymentId = QInputDialog::getText(this,
                               "Generate Certificate",
                               "Payment ID:",
                               QLineEdit::Normal,
                               QString(),
                               &ok);
        if (!ok || paymentId.trimmed().isEmpty()) return;
        std::string certId = adminController.generateCertificate(paymentId.toStdString());
        if (!certId.empty()) {
            QMessageBox::information(this,
                "Success",
                QString("Certificate generated with ID: %1").arg(QString::fromStdString(certId)));
        } else {
            QMessageBox::critical(this,
                "Error",
                "Failed to generate certificate. Please check payment ID.");
        }
    });
}

void AdminView::setupQnaTab() {
    QVBoxLayout * layout = new QVBoxLayout(qnaTab);

    // Table of pending questions
    QTableWidget *qnaTable = new QTableWidget();
    qnaTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    qnaTable->setSelectionMode(QAbstractItemView::SingleSelection);
    qnaTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qnaTable->setAlternatingRowColors(true);
    QStringList headers = {"ID","Student ID","Name","Timestamp","Question"};
    qnaTable->setColumnCount(headers.size());
    qnaTable->setHorizontalHeaderLabels(headers);
    qnaTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(qnaTable);

    // Input for answer
    layout->addWidget(new QLabel("Answer selected question:"));
    QTextEdit *answerEdit = new QTextEdit();
    answerEdit->setFixedHeight(100);
    layout->addWidget(answerEdit);

    // Buttons
    QPushButton *loadBtn = new QPushButton("Load Questions");
    QPushButton *submitBtn = new QPushButton("Submit Answer");
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(loadBtn);
    btnLayout->addWidget(submitBtn);
    layout->addLayout(btnLayout);

    // Load pending questions
    connect(loadBtn, &QPushButton::clicked, [this, qnaTable]() {
        qnaTable->setRowCount(0);
        auto list = adminController.getPendingQuestions();
        for (int i = 0; i < (int)list.size(); ++i) {
            const auto &q = list[i];
            qnaTable->insertRow(i);
            qnaTable->setItem(i, 0, new QTableWidgetItem(QString::number(q.getId())));
            qnaTable->setItem(i, 1, new QTableWidgetItem(QString::number(q.getStudentId())));
            qnaTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(q.getStudentName())));
            QString tstr = QDateTime::fromSecsSinceEpoch(q.getTimestamp()).toString(QLocale().dateFormat(QLocale::ShortFormat));
            qnaTable->setItem(i, 3, new QTableWidgetItem(tstr));
            qnaTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(q.getQuestionText())));
        }
    });

    // Submit answer for selected question
    connect(submitBtn, &QPushButton::clicked, [this, qnaTable, answerEdit, loadBtn]() {
        int row = qnaTable->currentRow();
        if (row < 0) {
            QMessageBox::warning(this, "Warning", "Select a question first.");
            return;
        }
        QString idStr = qnaTable->item(row, 0)->text();
        int qid = idStr.toInt();
        QString ans = answerEdit->toPlainText().trimmed();
        if (ans.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Answer cannot be empty.");
            return;
        }
        bool ok = adminController.answerQuestionById(qid, ans.toStdString());
        if (ok) {
            QMessageBox::information(this, "Success", "Answer submitted.");
            answerEdit->clear();
            // refresh list
            loadBtn->click();
        } else {
            QMessageBox::critical(this, "Error", "Failed to submit answer.");
        }
    });
}