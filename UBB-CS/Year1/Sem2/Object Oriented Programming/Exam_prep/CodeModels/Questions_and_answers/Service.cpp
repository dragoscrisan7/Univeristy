//
// Created by Dragos on 6/29/2022.
//

#include "Service.h"

Service::Service(Repository &repo) : repo(repo) {}

Service::~Service() {

}

int Service::number_answers(int qid) {
    int cont = 0;
    for(auto a: repo.get_answers()){
        if(a.getQid() == qid){
            cont += 1;
        }
    }
    return cont;
}

vector<Question> Service::sort_questions() {
    vector<Question> v = repo.get_questions();
    vector<Answer> a = repo.get_answers();
    sort(v.begin(), v.end(), [&](Question q1, Question q2){return number_answers(q1.getId())>number_answers(q2.getId());});
    return v;
}

void Service::add_question(string text, string user_name) {
    int id = this->repo.get_questions().back().getId() + 1;
    Question q(id, text, user_name);
    this->repo.add_q(q);
    notify();
}

vector<Answer> Service::answers_to_q(int qid) {
    vector<Answer> v;
    vector<Answer> source = repo.get_answers();
    copy_if(source.begin(), source.end(), back_inserter(v), [&](Answer a){return a.getQid() == qid;});
    return v;
}

void Service::add_answer(int qid, string text, string user_name) {
    int id = this->repo.get_answers().back().getId() + 1;
    Answer a(id, qid, text, user_name, 0);
    repo.add_a(a);
    notify();
}

void Service::change_votes(int aid, int votes) {
    vector<Answer>& source = repo.get_answers();
    auto a = find_if(source.begin(), source.end(), [&](const Answer& a1){return a1.getId() == aid;});
    if(a->getVotes() == votes){
        return;
    }

    a->setVotes(votes);
    notify();
}
