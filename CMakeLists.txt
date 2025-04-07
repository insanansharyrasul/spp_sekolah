cmake_minimum_required(VERSION 3.10.0)
project(spp_sekolah VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include include/data_structure include/account)

file(GLOB_RECURSE SOURCE "src/*.cpp")

add_executable(spp_sekolah ${SOURCE})

