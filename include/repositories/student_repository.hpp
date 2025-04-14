#pragma once
#include <models/payment.hpp>
#include <models/student.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class StudentRepository {
   private:
    std::unordered_map<int, Student> students;
    std::string dataFilePath;

   public:
    StudentRepository(const std::string& filePath);

    // CRUD operations
    bool add(const Student& student);
    Student* findById(int id);
    std::vector<Student> findAll();
    bool update(const Student& student);
    bool remove(int id);

    // Persistence
    bool loadFromFile();
    bool saveToFile();
};