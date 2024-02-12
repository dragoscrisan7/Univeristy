#pragma once
#include "Repository.h"
#include "Observer.h"

class Service: public Subject{
private:
    Repository& repo;
public:
    Service(Repository& repos): repo(repos){}

    void add_question(int id, std::string text, std::string correct_answer, int score);
    bool is_answer(int id, std::string answer);
    int get_question_score(int id);
    std::vector<Question> sorted_by_id();
    std::vector<Question> sorted_by_score();
};

