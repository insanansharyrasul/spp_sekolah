#pragma once
#include <models/question.hpp>
#include <repositories/question_repository.hpp>
#include <map>
#include <string>
#include <vector>

class QnAService {
private:
    QuestionRepository& questionRepo;

public:
    QnAService(QuestionRepository& repo) : questionRepo(repo) {}
    
    int submitQuestion(int studentId, const std::string& studentName, const std::string& questionText) {
        return questionRepo.addQuestion(studentId, studentName, questionText);
    }
    
    bool hasQuestionsToAnswer() const {
        return questionRepo.hasPendingQuestions();
    }
    
    Question getNextQuestion() {
        return questionRepo.getNextPendingQuestion();
    }
    
    void answerQuestion(const std::string& answer) {
        Question question = questionRepo.getNextPendingQuestion();
        questionRepo.answerQuestion(question.getId(), answer);
    }
    
    std::vector<Question> getAnsweredQuestionsForStudent(int studentId) {
        return questionRepo.getAnsweredQuestionsByStudentId(studentId);
    }
    
    int getQueueSize() const {
        return questionRepo.getPendingCount();
    }
};
