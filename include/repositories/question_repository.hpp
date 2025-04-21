#pragma once
#include <models/question.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class QuestionRepository {
private:
    std::vector<Question> pendingQuestions;
    std::map<int, std::vector<Question>> answeredQuestions; // Maps studentId to their answered questions
    std::string dataFilePath;
    int nextQuestionId;

public:
    QuestionRepository(const std::string& filePath);

    // CRUD operations
    int addQuestion(int studentId, const std::string& studentName, const std::string& questionText);
    bool answerQuestion(int questionId, const std::string& answer);
    Question* getPendingQuestionById(int questionId);
    std::vector<Question> getAllPendingQuestions() const;
    std::vector<Question> getAnsweredQuestionsByStudentId(int studentId) const;
    
    // Queue operations
    Question getNextPendingQuestion() const;
    bool hasPendingQuestions() const;
    int getPendingCount() const;

    // Persistence
    bool loadFromFile();
    bool saveToFile();
};
