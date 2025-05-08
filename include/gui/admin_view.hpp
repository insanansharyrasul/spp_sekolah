#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <controllers/admin_controller.hpp>

class AdminView : public QWidget {
    Q_OBJECT

public:
    explicit AdminView(AdminController& controller, QWidget *parent = nullptr);
    ~AdminView();

    void setupDashboard();

private:
    void setupStudentTab();
    void setupPaymentTab();
    void setupCertificateTab();
    void setupQnaTab();

    // UI elements
    QTabWidget *tabWidget;
    QWidget *studentTab;
    QWidget *paymentTab;
    QWidget *certTab;
    QWidget *qnaTab;

    // Controller reference
    AdminController& adminController;
};