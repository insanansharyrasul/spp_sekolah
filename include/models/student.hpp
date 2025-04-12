#pragma once
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
};
