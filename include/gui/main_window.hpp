#pragma once

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QString>
#include <QTabWidget>
#include <controllers/admin_controller.hpp>
#include <controllers/student_controller.hpp>
#include <repositories/certificate_repository.hpp>
#include <repositories/payment_repository.hpp>
#include <repositories/question_repository.hpp>
#include <repositories/student_repository.hpp>
#include <services/payment_service.hpp>
#include <services/qna_service.hpp>

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private:
    void setupUi();
    void createMenus();
    void createActions();

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
    QTabWidget *tabWidget;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *exitAction;
    QAction *aboutAction;
    QStatusBar *statusBar;
};