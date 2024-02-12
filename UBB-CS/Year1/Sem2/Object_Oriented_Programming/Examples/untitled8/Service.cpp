#include "Service.h"
#include <exception>
#include <algorithm>

void Service::add_question(int id, std::string text, std::string correct_answer, int score) {
    if(text.empty())
        throw "Failed!\nEmpty question!";
    if (repo.get_index_for_id(id)!=-1)
        throw "Failed!\nQuestion already exists!";
    Question q{id, text, correct_answer, score};
    repo.add(q);
    this->notify();
}

bool Service::is_answer(int id, std::string answer) {
    int index = this->repo.get_index_for_id(id);
    if (this->repo[index].getCorrectAnswer() == answer)
        return true;
    return false;
}

int Service::get_question_score(int id) {
    int index = this->repo.get_index_for_id(id);
    return this->repo[index].getScore();
}

std::vector<Question> Service::sorted_by_id() {
    std::vector<Question> sorted = this->repo.get_all_questions();
    std::sort(sorted.begin(), sorted.end(), [](const Question& q1, const Question& q2){return q1.getId()<q2.getId();});
    return sorted;
}

std::vector<Question> Service::sorted_by_score() {
    std::vector<Question> sorted = this->repo.get_all_questions();
    std::sort(sorted.begin(), sorted.end(), [](const Question& q1, const Question& q2){return q1.getScore()<q2.getScore();});
    return sorted;
}


