#include <application/spp_application.hpp>

// Then your main.cpp becomes very simple
int main() {
    SppApplication app;
    app.initialize();
    app.run();
    return 0;
}