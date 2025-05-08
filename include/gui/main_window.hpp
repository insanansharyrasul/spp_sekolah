#pragma once

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QString>
#include <QStackedWidget>
#include <controllers/admin_controller.hpp>
#include <controllers/student_controller.hpp>
#include <repositories/certificate_repository.hpp>
#include <repositories/payment_repository.hpp>
#include <repositories/question_repository.hpp>
#include <repositories/student_repository.hpp>
#include <services/payment_service.hpp>
#include <services/qna_service.hpp>
#include "gui/login_view.hpp"
#include "gui/admin_view.hpp"
#include "gui/student_view.hpp"

// User session to manage authentication state
class UserSession {
public:
    bool isAuthenticated;
    bool isAdmin;
    bool isStudent;
    int currentStudentId;

    UserSession() : isAuthenticated(false), isAdmin(false), isStudent(false), currentStudentId(-1) {}
};

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:
    void showLoginScreen();
    void adminLogin(const QString& username, const QString& password);
    void studentLogin(int studentId);
    void logout();
    void showAdminDashboard();
    void showStudentDashboard();

   private:
    void setupUi();
    void createMenus();
    void createActions();

    // Session management
    UserSession session;

    // Repositories
    StudentRepository studentRepo;
    PaymentRepository paymentRepo;
    CertificateRepository certificateRepo;
    QuestionRepository questionRepo;

    // Services
    StudentService studentService;
    PaymentService paymentService;
    CertificateService certService;
    QnAService qnaService;

    // Controllers
    AdminController adminController;
    StudentController studentController;

    // UI elements
    QStackedWidget *stackedWidget;
    LoginView *loginView;
    AdminView *adminView;
    StudentView *studentView;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *logoutAction;
    QStatusBar *statusBar;
};