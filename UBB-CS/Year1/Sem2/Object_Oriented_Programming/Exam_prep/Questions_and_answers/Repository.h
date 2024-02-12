//
// Created by Dragos on 6/28/2022.
//

#ifndef QUESTIONS_AND_ANSWERS_REPOSITORY_H
#define QUESTIONS_AND_ANSWERS_REPOSITORY_H
#include "User.h"
#include "Question.h"
#include "Answer.h"

class Repository {
private:
    vector<User> users;
    string users_file = "C:\\Users\\Dragos\\CLionProjects\\Questions_and_answers\\Users.txt";
    vector<Question> questions;
    string q_file = "C:\\Users\\Dragos\\CLionProjects\\Questions_and_answers\\Questions.txt";
    vector<Answer> answers;
    string a_file = "C:\\Users\\Dragos\\CLionProjects\\Questions_and_answers\\Answers.txt";
public:
    Repository();

    virtual ~Repository();

    void read_from_file();
    void save_to_file();
    vector<User>& get_users();
    vector<Question> get_questions();
    vector<Answer>& get_answers();

    void add_q(Question& q);
    void add_a(Answer& a);
};


#endif //QUESTIONS_AND_ANSWERS_REPOSITORY_H
