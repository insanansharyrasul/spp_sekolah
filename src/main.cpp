#include <QApplication>
#include <application/spp_application.hpp>
#include <gui/main_window.hpp>
#include <utils/ui_helpers.hpp>

int main(int argc, char *argv[]) {
    int choice;
    UI::clrscr();
    std::cout << UI::Color::BLUE << "Welcome to the School Payment Management System!" << std::endl;
    std::cout << UI::Color::BLUE << "Please choose an option:" << std::endl;
    std::cout << UI::Color::BLUE << "1. CLI Application" << std::endl;
    std::cout << UI::Color::BLUE << "2. Qt Application" << std::endl;
    std::cout << UI::Color::BLUE << "3. Exit" << std::endl;
    std::cin >> choice;
    if (choice == 1) {
        SppApplication app;
        app.initialize();
        app.run();
        return 0;
    } else if (choice == 2) {
        QApplication app(argc, argv);
        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
    } else if (choice == 3) {
        UI::clrscr();
        std::cout << UI::Color::BLUE << "Exiting..." << std::endl;
        return 0;
    } else {
        std::cout << UI::Color::RED << "Invalid choice. Exiting..." << std::endl;
        return 1;
    }
}