#include "gui/login_view.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFont>
#include <QMessageBox>

LoginView::LoginView(QWidget *parent) : QWidget(parent) {
    setupUi();
}

LoginView::~LoginView() {}

void LoginView::setupUi() {
    QVBoxLayout *mainLoginLayout = new QVBoxLayout(this);
    loginStackedWidget = new QStackedWidget();
    
    QLabel *titleLabel = new QLabel("SCHOOL PAYMENT MANAGEMENT SYSTEM");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    
    QWidget *loginTypeWidget = new QWidget();
    QVBoxLayout *loginTypeLayout = new QVBoxLayout(loginTypeWidget);
    
    QLabel *loginPrompt = new QLabel("Please select login type:");
    loginPrompt->setAlignment(Qt::AlignCenter);
    
    adminLoginBtn = new QPushButton("Login as Admin");
    studentLoginBtn = new QPushButton("Login as Student");
    loginCancelBtn = new QPushButton("Exit");
    
    loginTypeLayout->addWidget(loginPrompt);
    loginTypeLayout->addWidget(adminLoginBtn);
    loginTypeLayout->addWidget(studentLoginBtn);
    loginTypeLayout->addWidget(loginCancelBtn);
    loginTypeLayout->setContentsMargins(100, 20, 100, 20);
    
    adminLoginWidget = new QWidget();
    QGridLayout *adminLoginLayout = new QGridLayout(adminLoginWidget);
    
    QLabel *adminLoginTitle = new QLabel("ADMIN LOGIN");
    QFont adminTitleFont = adminLoginTitle->font();
    adminTitleFont.setBold(true);
    adminLoginTitle->setFont(adminTitleFont);
    adminLoginTitle->setAlignment(Qt::AlignCenter);
    
    QLabel *usernameLabel = new QLabel("Username:");
    QLabel *passwordLabel = new QLabel("Password:");
    
    usernameInput = new QLineEdit();
    passwordInput = new QLineEdit();
    passwordInput->setEchoMode(QLineEdit::Password);
    
    QPushButton *adminSubmitBtn = new QPushButton("Login");
    QPushButton *adminBackBtn = new QPushButton("Back");
    
    adminLoginLayout->addWidget(adminLoginTitle, 0, 0, 1, 2);
    adminLoginLayout->addWidget(usernameLabel, 1, 0);
    adminLoginLayout->addWidget(usernameInput, 1, 1);
    adminLoginLayout->addWidget(passwordLabel, 2, 0);
    adminLoginLayout->addWidget(passwordInput, 2, 1);
    adminLoginLayout->addWidget(adminSubmitBtn, 3, 0);
    adminLoginLayout->addWidget(adminBackBtn, 3, 1);
    adminLoginLayout->setContentsMargins(100, 20, 100, 20);
    
    studentLoginWidget = new QWidget();
    QGridLayout *studentLoginLayout = new QGridLayout(studentLoginWidget);
    
    QLabel *studentLoginTitle = new QLabel("STUDENT LOGIN");
    QFont studentTitleFont = studentLoginTitle->font();
    studentTitleFont.setBold(true);
    studentLoginTitle->setFont(studentTitleFont);
    studentLoginTitle->setAlignment(Qt::AlignCenter);
    
    QLabel *studentIdLabel = new QLabel("Student ID:");
    
    studentIdInput = new QLineEdit();
    
    QPushButton *studentSubmitBtn = new QPushButton("Login");
    QPushButton *studentBackBtn = new QPushButton("Back");
    
    studentLoginLayout->addWidget(studentLoginTitle, 0, 0, 1, 2);
    studentLoginLayout->addWidget(studentIdLabel, 1, 0);
    studentLoginLayout->addWidget(studentIdInput, 1, 1);
    studentLoginLayout->addWidget(studentSubmitBtn, 2, 0);
    studentLoginLayout->addWidget(studentBackBtn, 2, 1);
    studentLoginLayout->setContentsMargins(100, 20, 100, 20);
    
    loginStackedWidget->addWidget(loginTypeWidget);
    loginStackedWidget->addWidget(adminLoginWidget);
    loginStackedWidget->addWidget(studentLoginWidget);
    
    mainLoginLayout->addWidget(titleLabel);
    mainLoginLayout->addWidget(loginStackedWidget);
    
    connect(adminLoginBtn, &QPushButton::clicked, [this]() {
        usernameInput->clear();
        passwordInput->clear();
        loginStackedWidget->setCurrentWidget(adminLoginWidget);
    });
    
    connect(studentLoginBtn, &QPushButton::clicked, [this]() {
        studentIdInput->clear();
        loginStackedWidget->setCurrentWidget(studentLoginWidget);
    });
    
    connect(loginCancelBtn, &QPushButton::clicked, [this]() {
        if (onCancel) {
            onCancel();
        }
    });
    
    connect(adminSubmitBtn, &QPushButton::clicked, [this]() {
        if (onAdminLogin) {
            onAdminLogin(usernameInput->text(), passwordInput->text());
        }
    });
    
    connect(studentSubmitBtn, &QPushButton::clicked, [this]() {
        bool ok;
        int studentId = studentIdInput->text().toInt(&ok);
        
        if (!ok) {
            QMessageBox::warning(this, "Error", "Please enter a valid student ID (numbers only)!");
            return;
        }
        
        if (onStudentLogin) {
            onStudentLogin(studentId);
        }
    });
    
    connect(adminBackBtn, &QPushButton::clicked, [this]() {
        loginStackedWidget->setCurrentWidget(loginStackedWidget->widget(0)); 
    });
    
    connect(studentBackBtn, &QPushButton::clicked, [this]() {
        loginStackedWidget->setCurrentWidget(loginStackedWidget->widget(0)); 
    });
}

void LoginView::setAdminLoginCallback(std::function<void(const QString&, const QString&)> callback) {
    onAdminLogin = callback;
}

void LoginView::setStudentLoginCallback(std::function<void(int)> callback) {
    onStudentLogin = callback;
}

void LoginView::setCancelCallback(std::function<void()> callback) {
    onCancel = callback;
}

void LoginView::resetInputs() {
    usernameInput->clear();
    passwordInput->clear();
    studentIdInput->clear();
}

void LoginView::showLoginTypeSelection() {
    loginStackedWidget->setCurrentIndex(0); 
}