#pragma once

#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<int, std::string>> load_students();
void sort_students_by_name();
void sort_students_by_id();
void print_students();