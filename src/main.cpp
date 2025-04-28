#include <application/spp_application.hpp>
#include <QApplication>
#include <gui/main_window.hpp>

int main(int argc, char *argv[]) {
    // SppApplication app;
    // app.initialize();
    // app.run();
    // return 0;
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}