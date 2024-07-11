//
// Created by Dragos on 6/27/2022.
//

#include "Service.h"

Service::Service(QRepo &qr) : qr(qr) {}

Service::~Service() {

}

vector<Questions> Service::sorted_by_id() {
    vector<Questions> v = qr.getALL();
    sort(v.begin(), v.end(), [](const Questions q1, const Questions q2){return q1.getId()<q2.getId();});
    return v;
}

vector<Questions> Service::sorted_by_score() {
    vector<Questions> v = qr.getALL();
    sort(v.begin(), v.end(), [](const Questions q1, const Questions q2){return q1.getScore()>q2.getScore();});
    return v;
}

void Service::add(int id, string text, string correct_answer, int score) {
    if(text.empty())
        throw "incorrect text";
    if(qr.find_by_id(id) != -1)
        throw "question already exists";
    Questions q(id, score, text, correct_answer);
    qr.add_question(q);
    this->notify();
}

int Service::answer(int id, string answer) {
    int score = qr.answer_question(id, answer);
    return score;
}
