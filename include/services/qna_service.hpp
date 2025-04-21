#pragma once
#include <data_structures/SimpleQueue.hpp>
#include <models/question.hpp>
#include <vector>
#include <map>

class QnAService {
private:
    SimpleQueue<Question> questionQueue;
    std::map<int, std::vector<Question>> answeredQuestions; // Maps studentId to their answered questions
    int nextQuestionId;

public:
    QnAService() : nextQuestionId(1) {}
    
    int submitQuestion(int studentId, const std::string& studentName, const std::string& questionText) {
        Question newQuestion(nextQuestionId++, studentId, studentName, questionText);
        questionQueue.enqueue(newQuestion);
        return newQuestion.getId();
    }
    
    bool hasQuestionsToAnswer() const {
        return !questionQueue.isEmpty();
    }
    
    Question getNextQuestion() {
        if (questionQueue.isEmpty()) {
            throw std::runtime_error("No questions available");
        }
        return questionQueue.peek();
    }
    
    void answerQuestion(const std::string& answer) {
        if (questionQueue.isEmpty()) {
            throw std::runtime_error("No questions to answer");
        }
        
        Question question = questionQueue.dequeue();
        question.setAnswer(answer);
        
        // Store answered question for student retrieval
        int studentId = question.getStudentId();
        answeredQuestions[studentId].push_back(question);
    }
    
    std::vector<Question> getAnsweredQuestionsForStudent(int studentId) {
        if (answeredQuestions.find(studentId) != answeredQuestions.end()) {
            return answeredQuestions[studentId];
        }
        return std::vector<Question>();
    }
    
    int getQueueSize() const {
        return questionQueue.getSize();
    }
};
