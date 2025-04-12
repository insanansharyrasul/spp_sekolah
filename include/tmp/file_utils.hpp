#pragma once
#include <data.hpp>
#include <unordered_map>
#include <vector>

std::unordered_map<size_t, std::string> load_certificate_map();
std::unordered_map<std::string, PembayaranSPP> load_spp_map();
std::unordered_map<int, Student> load_students_map();

void append_student(Student);
void append_spp(PembayaranSPP);
void append_certificate(size_t, std::string);

extern std::unordered_map<size_t, std::string> CERTIFICATE_DATA;
extern std::unordered_map<std::string, PembayaranSPP> SPP_DATA;
extern std::unordered_map<int, Student> STUDENT_DATA;