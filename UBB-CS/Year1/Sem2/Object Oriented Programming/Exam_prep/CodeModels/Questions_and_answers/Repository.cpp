//
// Created by Dragos on 6/28/2022.
//

#include "Repository.h"

Repository::Repository(){
    read_from_file();
}

Repository::~Repository() {
    save_to_file();
}

#include <fstream>

void Repository::read_from_file() {
    std::ifstream f(users_file);
    while(!f.eof()){
        User q;
        f>> q;
        if(q.getName().empty())
            break;
        this->users.push_back(q);
    }
    f.close();

    std::ifstream f2(q_file);
    while(!f2.eof()){
        Question q;
        f2>> q;
        if(q.getText().empty())
            break;
        this->questions.push_back(q);
    }
    f.close();

    std::ifstream f3(a_file);
    while(!f3.eof()){
        Answer q;
        f3>> q;
        if(q.getText().empty())
            break;
        this->answers.push_back(q);
    }
    f.close();

}

void Repository::save_to_file() {
    std::ofstream f(users_file);
    f.clear();
    for(const auto& q:users){
        f<<q<<"\n";
    }
    f.close();

    std::ofstream f2(q_file);
    f2.clear();
    for(const auto& q:questions){
        f2<<q<<"\n";
    }
    f2.close();

    std::ofstream f3(a_file);
    f3.clear();
    for(const auto& q:answers){
        f3<<q<<"\n";
    }
    f3.close();
}

vector<User>& Repository::get_users() {
    return users;
}

vector<Question> Repository::get_questions() {
    return questions;
}

vector<Answer>& Repository::get_answers() {
    return answers;
}

void Repository::add_q(Question &q) {
    questions.push_back(q);
}

void Repository::add_a(Answer &a) {
    answers.push_back(a);
}
