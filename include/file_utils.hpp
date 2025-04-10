#pragma once
#include <data.hpp>
#include <unordered_map>
#include <vector>

std::unordered_map<int, PembayaranSPP> load_spp_map();
std::unordered_map<size_t, std::string> load_certificate_map();
std::vector<Student> load_students_vector();
