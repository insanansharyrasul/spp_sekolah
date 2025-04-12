cmake_minimum_required(VERSION 3.10.0)
project(spp_sekolah VERSION 0.1.0 LANGUAGES C CXX)

include_directories(
    include 
    include/application
    include/controllers 
    include/models 
    include/repositories 
    include/services
    include/utils
)

file(GLOB SOURCE 
    "src/main.cpp"
    "src/application/*.cpp"
    "src/models/*.cpp"
    "src/controllers/*.cpp"
    "src/repositories/*.cpp"
    "src/services/*.cpp"
    "src/utils/*.cpp"
)

add_executable(spp_sekolah ${SOURCE})

