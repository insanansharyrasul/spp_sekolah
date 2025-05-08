#include <gui/main_window.hpp>
#include <gui/login_view.hpp>
#include <gui/admin_view.hpp>
#include <gui/student_view.hpp>

#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QFont>
#include <QTextEdit>

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
      studentController(studentService, paymentService, qnaService, certService) {
    
    if (!studentRepo.loadFromFile()) {
        QMessageBox::critical(this, "Error", "Failed to load student data! Trying to create a new file...");
    }
    if (!paymentRepo.loadFromFile()) {
        QMessageBox::critical(this, "Error", "Failed to load payment data! Trying to create a new file...");
    }
    if (!questionRepo.loadFromFile()) {
        QMessageBox::warning(this, "Warning", "Failed to load question data! Trying to create a new file...");
    }
    
    setupUi();
    createActions();
    createMenus();

    setWindowTitle("School Payment Management System");
    resize(800, 600);
    
    showLoginScreen();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    loginView = new LoginView();
    adminView = new AdminView(adminController);
    studentView = new StudentView(studentController);
    
    stackedWidget->addWidget(loginView);
    stackedWidget->addWidget(adminView);
    stackedWidget->addWidget(studentView);
    
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    statusBar->showMessage("Please log in");
    
    loginView->setAdminLoginCallback([this](const QString& username, const QString& password) {
        adminLogin(username, password);
    });
    
    loginView->setStudentLoginCallback([this](int studentId) {
        studentLogin(studentId);
    });
    
    loginView->setCancelCallback([this]() {
        close();
    });
}

void MainWindow::adminLogin(const QString& username, const QString& password) {
    if (username == "admin" && password == "admin123") {
        session.isAuthenticated = true;
        session.isAdmin = true;
        session.isStudent = false;
        
        QMessageBox::information(this, "Success", "Login successful!");
        showAdminDashboard();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
    }
}

void MainWindow::studentLogin(int studentId) {
    Student* student = studentRepo.findById(studentId);
    if (student) {
        session.isAuthenticated = true;
        session.isAdmin = false;
        session.isStudent = true;
        session.currentStudentId = studentId;
        
        QMessageBox::information(this, "Success", "Login successful! Welcome, " + QString::fromStdString(student->getName()) + "!");
        showStudentDashboard();
    } else {
        QMessageBox::warning(this, "Login Failed", "Student not found!");
    }
}

void MainWindow::showLoginScreen() {
    session.isAuthenticated = false;
    session.isAdmin = false;
    session.isStudent = false;
    session.currentStudentId = -1;
    
    loginView->resetInputs();
    loginView->showLoginTypeSelection();
    stackedWidget->setCurrentWidget(loginView);
    statusBar->showMessage("Please log in");
}

void MainWindow::logout() {
    showLoginScreen();
}

void MainWindow::showAdminDashboard() {
    if (!session.isAuthenticated || !session.isAdmin) {
        return;
    }
    
    adminView->setupDashboard();
    
    stackedWidget->setCurrentWidget(adminView);
    statusBar->showMessage("Logged in as Administrator");
}

void MainWindow::showStudentDashboard() {
    if (!session.isAuthenticated || !session.isStudent) {
        return;
    }
    
    studentView->setupDashboard(session.currentStudentId);
    
    stackedWidget->setCurrentWidget(studentView);
    
    Student* student = studentRepo.findById(session.currentStudentId);
    statusBar->showMessage("Logged in as Student: " + QString::fromStdString(student ? student->getName() : ""));
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
    
    logoutAction = new QAction("&Logout", this);
    connect(logoutAction, &QAction::triggered, this, &MainWindow::logout);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu("&Session");
    fileMenu->addAction(logoutAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
}