#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <controllers/student_controller.hpp>
#include <models/student.hpp>

class StudentView : public QWidget {
    Q_OBJECT

public:
    explicit StudentView(StudentController& controller, QWidget *parent = nullptr);
    ~StudentView();

    void setupDashboard(int studentId);

private:
    void setupInfoTab(Student* student);
    void setupPaymentTab();
    void setupCertificateTab();
    void setupQnaTab();
    void setupAnsweredTab();

    // UI elements
    QTabWidget *tabWidget;
    QWidget *infoTab;
    QWidget *paymentTab;
    QWidget *certTab;
    QWidget *qnaTab;
    QWidget *answeredQnaTab;
    QTextEdit *questionEdit;
    QSpinBox *monthSpinBox;
    QSpinBox *yearSpinBox;
    QPushButton *showByDateBtn;
    QPushButton *showLatestBtn;
    QTextEdit *paymentDisplay;
    QLineEdit *certIdLineEdit;
    QTextEdit *certDisplay;
    QPushButton *viewCertBtn;
    QPushButton *showAnsweredBtn;
    QTextEdit *answeredDisplay;

    // Controller reference
    StudentController& studentController;
    int currentStudentId;
};