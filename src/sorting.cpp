#include <sorting.hpp>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <file_path.hpp>
#include <file_utils.hpp>
#include <data.hpp>
#include <iomanip>
#include <vector>
using namespace std;

void sort_students_by_name() {
    vector<Student> students = load_students_vector();
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.nama < b.nama;
    });
    for (const Student& student : students) {
        cout << setw(8) << left << student.id_student << setw(12) << left << student.nama << endl;
    }
}

void sort_students_by_id() {
    vector<Student> students = load_students_vector();
    sort(students.begin(), students.end(), [](Student& a, Student& b) {
        return a.id_student < b.id_student;
    });
    for (const Student& student : students) {
        cout << setw(8) << left << student.id_student << setw(12) << left << student.nama << endl;
    }
}