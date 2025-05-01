#include "gui/admin_view.hpp"

#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>

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
    QPushButton *registerStudentBtn = new QPushButton("Register New Student");

    studentLayout->addWidget(studentTable);
    studentLayout->addWidget(viewStudentsBtn);
    studentLayout->addWidget(registerStudentBtn);

    connect(viewStudentsBtn, &QPushButton::clicked, [this, studentTable]() {
        studentTable->setRowCount(0);

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

        studentTable->sortByColumn(0, Qt::AscendingOrder);
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

    connect(viewPaymentsBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "Information", "View Payments functionality to be implemented");
    });

    connect(setPaymentBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "Information", "Set Payment functionality to be implemented");
    });
}

void AdminView::setupCertificateTab() {
    QVBoxLayout *certLayout = new QVBoxLayout(certTab);

    QPushButton *makeCertBtn = new QPushButton("Generate Certificate");
    certLayout->addWidget(makeCertBtn);

    connect(makeCertBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "Information", "Generate Certificate functionality to be implemented");
    });
}

void AdminView::setupQnaTab() {
    QVBoxLayout *qnaLayout = new QVBoxLayout(qnaTab);

    QPushButton *answerQuestionsBtn = new QPushButton("Answer Student Questions");
    qnaLayout->addWidget(answerQuestionsBtn);

    connect(answerQuestionsBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "Information", "Answer Questions functionality to be implemented");
    });
}