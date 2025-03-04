cmake_minimum_required(VERSION 3.10.0)
project(spp_sekolah VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)
add_executable(spp_sekolah src/main.cpp src/menu.cpp src/payment.cpp)

