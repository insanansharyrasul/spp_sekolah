#pragma once
#include <repositories/student_repository.hpp>

class StudentService {
private:
    StudentRepository& studentRepo;
    
public:
    StudentService(StudentRepository& repo);
    
    bool registerStudent(const std::string& name, int yearEnrolled, int classId);
    Student* getStudentById(int id);
    std::vector<Student> getAllStudents();
    bool updateStudent(int id, const std::string& name, int classId);
};