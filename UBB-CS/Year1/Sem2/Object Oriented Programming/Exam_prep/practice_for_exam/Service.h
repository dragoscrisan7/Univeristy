//
// Created by Oana on 6/6/2022.
//

#pragma once
#include "QuestionRepo.h"
#include "Observer.h"

class Service: public Subject {
private:
    QuestionRepo& repo;
public:
    Service(QuestionRepo& questionRepo): repo{ questionRepo } {}

    void add_question(int id, std::string text, std::string correct_answer, int score);
    bool is_answer(int id, std::string answer);
    int get_question_score(int id);
    std::vector<Question> sorted_by_id();
    std::vector<Question> sorted_by_score();
};

