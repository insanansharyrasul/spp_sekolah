#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QLabel>
#include <functional>

class LoginView : public QWidget {
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

    // Set callback functions for login events
    void setAdminLoginCallback(std::function<void(const QString&, const QString&)> callback);
    void setStudentLoginCallback(std::function<void(int)> callback);
    void setCancelCallback(std::function<void()> callback);
    
    void resetInputs();
    void showLoginTypeSelection();

private:
    void setupUi();

    // UI elements
    QStackedWidget *loginStackedWidget;
    QPushButton *adminLoginBtn;
    QPushButton *studentLoginBtn;
    QPushButton *loginCancelBtn;
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QLineEdit *studentIdInput;
    QWidget *adminLoginWidget;
    QWidget *studentLoginWidget;

    // Callback functions
    std::function<void(const QString&, const QString&)> onAdminLogin;
    std::function<void(int)> onStudentLogin;
    std::function<void()> onCancel;
};