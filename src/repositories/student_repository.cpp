#include <fstream>
#include <repositories/student_repository.hpp>
#include <sstream>

StudentRepository::StudentRepository(const std::string& filePath) : dataFilePath(filePath) {
    loadFromFile();
}

bool StudentRepository::loadFromFile() {
    std::ifstream inFile(dataFilePath);
    if (!inFile.is_open()) {
        return false;  // Failed to open file
    }

    students.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        int id, yearRegistered, classId;
        std::string name;

        ss >> id;
        ss.ignore();  
        ss >> yearRegistered;
        ss.ignore();  
        ss >> classId;
        ss.ignore();  
        std::getline(ss, name);

        students[id] = Student(id, name, yearRegistered, classId);
    }
    inFile.close();
    return true;
}

bool StudentRepository::saveToFile() {
    std::ofstream outFile(dataFilePath);
    if (!outFile.is_open()) {
        return false;  // Failed to open file
    }

    for (const auto& pair : students) {
        const Student& student = pair.second;
        outFile << student.getId() << ","
                << student.getYearRegistered() << ","
                << student.getClassId() << ","
                << student.getName() << "\n";
    }
    outFile.close();
    return true;
}

bool StudentRepository::add(const Student& student) {
    if (students.find(student.getId()) != students.end()) {
        return false;  // Student already exists
    }
    students[student.getId()] = student;
    return saveToFile();
}

Student* StudentRepository::findById(int id) {
    auto it = students.find(id);
    if (it != students.end()) {
        return &it->second;
    }
    return nullptr;  // Student not found
}

std::vector<Student> StudentRepository::findAll() {
    std::vector<Student> studentList;
    for (const auto& pair : students) {
        studentList.push_back(pair.second);
    }
    return studentList;
}

bool StudentRepository::update(const Student& student) {
    auto it = students.find(student.getId());
    if (it == students.end()) {
        return false;  // Student not found
    }
    it->second = student;
    return saveToFile();
}

bool StudentRepository::remove(int id) {
    auto it = students.find(id);
    if (it == students.end()) {
        return false;  // Student not found
    }
    students.erase(it);
    return saveToFile();
}