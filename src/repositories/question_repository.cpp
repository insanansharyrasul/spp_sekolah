#include <repositories/question_repository.hpp>
#include <sstream>
#include <iostream>
#include <algorithm>

QuestionRepository::QuestionRepository(const std::string& filePath) : dataFilePath(filePath), nextQuestionId(1) {
    loadFromFile();
}

int QuestionRepository::addQuestion(int studentId, const std::string& studentName, const std::string& questionText) {
    // Find the highest existing question ID to ensure uniqueness
    for (const auto& question : pendingQuestions) {
        if (question.getId() >= nextQuestionId) {
            nextQuestionId = question.getId() + 1;
        }
    }
    
    for (const auto& pair : answeredQuestions) {
        for (const auto& question : pair.second) {
            if (question.getId() >= nextQuestionId) {
                nextQuestionId = question.getId() + 1;
            }
        }
    }
    
    Question newQuestion(nextQuestionId++, studentId, studentName, questionText);
    pendingQuestions.push_back(newQuestion);
    saveToFile();
    return newQuestion.getId();
}

bool QuestionRepository::answerQuestion(int questionId, const std::string& answer) {
    // Find the question in pending questions
    auto it = std::find_if(pendingQuestions.begin(), pendingQuestions.end(),
                         [questionId](const Question& q) { return q.getId() == questionId; });
    
    if (it == pendingQuestions.end()) {
        return false;
    }
    
    // Set the answer
    it->setAnswer(answer);
    
    // Move to answered questions
    int studentId = it->getStudentId();
    answeredQuestions[studentId].push_back(*it);
    
    // Remove from pending questions
    pendingQuestions.erase(it);
    
    saveToFile();
    return true;
}

Question* QuestionRepository::getPendingQuestionById(int questionId) {
    for (auto& question : pendingQuestions) {
        if (question.getId() == questionId) {
            return &question;
        }
    }
    return nullptr;
}

std::vector<Question> QuestionRepository::getAllPendingQuestions() const {
    return pendingQuestions;
}

std::vector<Question> QuestionRepository::getAnsweredQuestionsByStudentId(int studentId) const {
    auto it = answeredQuestions.find(studentId);
    if (it != answeredQuestions.end()) {
        return it->second;
    }
    return std::vector<Question>();
}

Question QuestionRepository::getNextPendingQuestion() const {
    if (pendingQuestions.empty()) {
        throw std::runtime_error("No pending questions");
    }
    return pendingQuestions.front();
}

bool QuestionRepository::hasPendingQuestions() const {
    return !pendingQuestions.empty();
}

int QuestionRepository::getPendingCount() const {
    return pendingQuestions.size();
}

bool QuestionRepository::loadFromFile() {
    std::ifstream inFile(dataFilePath);
    if (!inFile.is_open()) {
        return false;
    }

    pendingQuestions.clear();
    answeredQuestions.clear();
    nextQuestionId = 1;
    
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string type, idStr, studentIdStr, timestampStr;
        int id, studentId;
        time_t timestamp;
        std::string studentName, questionText, answer;
        bool isAnswered;
        
        // Format: TYPE,ID,STUDENTID,STUDENTNAME,TIMESTAMP,QUESTION,ISANSWERED,ANSWER
        
        std::getline(ss, type, ',');
        std::getline(ss, idStr, ',');
        std::getline(ss, studentIdStr, ',');
        std::getline(ss, studentName, ',');
        std::getline(ss, timestampStr, ',');
        std::getline(ss, questionText, ',');
        
        id = std::stoi(idStr);
        studentId = std::stoi(studentIdStr);
        timestamp = std::stoll(timestampStr);
        
        if (type == "PENDING") {
            Question q(id, studentId, studentName, questionText);
            q.setTimestamp(timestamp);
            pendingQuestions.push_back(q);
        } else if (type == "ANSWERED") {
            std::string answerText;
            std::getline(ss, answerText);
            
            Question q(id, studentId, studentName, questionText);
            q.setTimestamp(timestamp);
            q.setAnswer(answerText);
            answeredQuestions[studentId].push_back(q);
        }
        
        // Keep track of the highest ID
        if (id >= nextQuestionId) {
            nextQuestionId = id + 1;
        }
    }
    
    inFile.close();
    return true;
}

bool QuestionRepository::saveToFile() {
    std::ofstream outFile(dataFilePath);
    if (!outFile.is_open()) {
        return false;
    }
    
    // Save pending questions
    for (const auto& q : pendingQuestions) {
        outFile << "PENDING," 
                << q.getId() << ","
                << q.getStudentId() << ","
                << q.getStudentName() << ","
                << q.getTimestamp() << ","
                << q.getQuestionText() << "\n";
    }
    
    // Save answered questions
    for (const auto& pair : answeredQuestions) {
        for (const auto& q : pair.second) {
            outFile << "ANSWERED,"
                    << q.getId() << ","
                    << q.getStudentId() << ","
                    << q.getStudentName() << ","
                    << q.getTimestamp() << ","
                    << q.getQuestionText() << ","
                    << q.getAnswer() << "\n";
        }
    }
    
    outFile.close();
    return true;
}
