#include "gui/main_window.hpp"

#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      studentRepo("../data/students.txt"),
      paymentRepo("../data/payments.txt"),
      certificateRepo("../data/certificates.txt"),
      questionRepo("../data/questions.txt"),
      paymentService(paymentRepo, studentRepo),
      studentService(studentRepo),
      certService(paymentRepo, certificateRepo, studentRepo),
      qnaService(questionRepo),
      adminController(studentService, paymentService, certService, qnaService),
      studentController(studentService, paymentService, qnaService) {
    setupUi();
    createActions();
    createMenus();

    setWindowTitle("School Payment Management System");
    resize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    // Create central widget with tab structure
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    // Add tabs for different functions
    QWidget *studentTab = new QWidget();
    QWidget *paymentTab = new QWidget();
    QWidget *adminTab = new QWidget();

    tabWidget->addTab(studentTab, "Students");
    tabWidget->addTab(paymentTab, "Payments");
    tabWidget->addTab(adminTab, "Administration");

    // Create basic layouts for tabs
    QVBoxLayout *studentLayout = new QVBoxLayout(studentTab);
    studentLayout->addWidget(new QLabel("Student Management Interface"));

    QVBoxLayout *paymentLayout = new QVBoxLayout(paymentTab);
    paymentLayout->addWidget(new QLabel("Payment Management Interface"));

    QVBoxLayout *adminLayout = new QVBoxLayout(adminTab);
    adminLayout->addWidget(new QLabel("Admin Interface"));

    // Create status bar
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    statusBar->showMessage("Ready");
}

void MainWindow::createActions() {
    exitAction = new QAction("E&xit", this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    aboutAction = new QAction("&About", this);
    connect(aboutAction, &QAction::triggered, [this]() {
        QMessageBox::about(this, "About SPP Sekolah",
                           "School Payment Management System\n"
                           "Version 0.1.0");
    });
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(exitAction);

    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
}