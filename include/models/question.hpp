#pragma once
#include <string>
#include <ctime>

class Question {
private:
    int id;
    int studentId;
    std::string studentName;
    std::string questionText;
    std::string answer;
    time_t timestamp;
    bool isAnswered;

public:
    Question(int id, int studentId, const std::string& studentName, 
             const std::string& questionText)
        : id(id), 
          studentId(studentId), 
          studentName(studentName),
          questionText(questionText), 
          answer(""), 
          timestamp(time(0)), 
          isAnswered(false) {}
    
    // Getters
    int getId() const { return id; }
    int getStudentId() const { return studentId; }
    std::string getStudentName() const { return studentName; }
    std::string getQuestionText() const { return questionText; }
    std::string getAnswer() const { return answer; }
    time_t getTimestamp() const { return timestamp; }
    bool getIsAnswered() const { return isAnswered; }
    
    // Setters
    void setAnswer(const std::string& answerText) {
        answer = answerText;
        isAnswered = true;
    }
};
