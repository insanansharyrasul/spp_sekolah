#include <models/student.hpp>
Student::Student(int id, const std::string& name, int yearRegistered, int classId) : id(id), name(name), yearRegistered(yearRegistered), classId(classId) {};

// Getter
int Student::getId() const { return id; }
std::string Student::getName() const { return name; }
int Student::getYearRegistered() const { return yearRegistered; }
int Student::getClassId() const { return classId; }

// Setter
void Student::setClassId(int classId) {
    this->classId = classId;
}

void Student::setName(const std::string& name) {
    this->name = name;
};

void Student::setYearRegistered(int yearRegistered) {
    this->yearRegistered = yearRegistered;
};