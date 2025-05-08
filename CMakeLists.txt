cmake_minimum_required(VERSION 3.10.0)
project(spp_sekolah VERSION 0.1.0 LANGUAGES C CXX)

# Qt MOC settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(
    include 
    include/application
    include/controllers 
    include/models 
    include/repositories 
    include/services
    include/utils
    include/gui
)

# Separate files with Q_OBJECT macro
set(GUI_FILES
    "include/gui/main_window.hpp"
    "src/gui/main_window.cpp"
    "include/gui/login_view.hpp"
    "src/gui/login_view.cpp"
    "include/gui/admin_view.hpp"
    "src/gui/admin_view.cpp"
    "include/gui/student_view.hpp"
    "src/gui/student_view.cpp"
)

# Other source files
file(GLOB OTHER_SOURCE 
    "src/main.cpp"
    "src/application/*.cpp"
    "src/models/*.cpp"
    "src/controllers/*.cpp"
    "src/repositories/*.cpp"
    "src/services/*.cpp"
    "src/utils/*.cpp"
)

# Combine sources
set(SOURCE ${GUI_FILES} ${OTHER_SOURCE})

add_executable(spp_sekolah ${SOURCE})
target_link_libraries(spp_sekolah Qt5::Widgets)