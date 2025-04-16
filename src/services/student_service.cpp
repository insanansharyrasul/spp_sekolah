#include "services/student_service.hpp"
#include <ctime>

StudentService::StudentService(StudentRepository& repo) : studentRepo(repo) {}

bool StudentService::registerStudent(const std::string& name, int yearEnrolled, int classId) {
    // Generate a unique ID
    int highestId = 0;
    for (const auto& student : studentRepo.findAll()) {
        if (student.getId() > highestId) highestId = student.getId();
    }
    
    int newId = highestId + 1;
    Student newStudent(newId, name, yearEnrolled, classId);
    
    return studentRepo.add(newStudent);
}

Student* StudentService::getStudentById(int id) {
    return studentRepo.findById(id);
}

std::vector<Student> StudentService::getAllStudents() {
    return studentRepo.findAll();
}

bool StudentService::updateStudent(int id, const std::string& name, int classId) {
    Student* student = studentRepo.findById(id);
    if (student) {
        student->setName(name);
        student->setClassId(classId);
        return studentRepo.update(*student);
    }
    return false;  // Student not found
}

std::string StudentService::getStudentName(int id) {
    Student* student = studentRepo.findById(id);
    if (student) {
        return student->getName();
    }
    return "";
}

bool StudentService::deleteStudent(int id) {
    return studentRepo.remove(id);
}