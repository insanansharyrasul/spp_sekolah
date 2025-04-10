#pragma once
#include <data.hpp>
#include <unordered_map>
#include <vector>


std::unordered_map<size_t, std::string> load_certificate_map();
std::vector<PembayaranSPP> load_spp_vector();
std::vector<Student> load_students_vector();

extern std::unordered_map<size_t, std::string> CERTIFICATE_DATA;
extern std::vector<PembayaranSPP> SPP_DATA;
extern std::vector<Student> STUDENT_DATA;