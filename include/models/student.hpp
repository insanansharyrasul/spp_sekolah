#pragma once
#include <iomanip>
#include <ostream>
#include <string>
class Student {
   private:
    int id;
    std::string name;
    int yearRegistered;
    int classId;

   public:
    Student(int id = 0, const std::string& name = "", int yearRegistered = 0, int classId = 0);

    // Getter
    int getId() const;
    std::string getName() const;
    int getYearRegistered() const;
    int getClassId() const;

    // Setter
    void setName(const std::string& name);
    void setYearRegistered(int year);
    void setClassId(int id);

    // Friend function for stream insertion
    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << std::setw(20) << std::left << "ID" << ": " << student.id << "\n"
           << std::setw(20) << std::left << "Nama" << ": " << student.name << "\n"
           << std::setw(20) << std::left << "Tahun Terdaftar" << ": " << student.yearRegistered << "\n"
           << std::setw(20) << std::left << "ID Kelas" << ": " << student.classId;
        return os;
    }
};
