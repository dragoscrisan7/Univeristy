//
// Created by Dragos on 6/28/2022.
//

#ifndef QUESTIONS_AND_ANSWERS_QUESTION_H
#define QUESTIONS_AND_ANSWERS_QUESTION_H
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Question {
private:
    int id;
    string text, user_name;
public:
    Question(int id, const string &text, const string &userName);

    Question();

    virtual ~Question();

    int getId() const;

    void setId(int id);

    const string &getText() const;

    void setText(const string &text);

    const string &getUserName() const;

    void setUserName(const string &userName);

    friend ostream &operator<<(ostream &os, const Question &question);
    friend istream &operator>>(istream &is, Question &question);
};


#endif //QUESTIONS_AND_ANSWERS_QUESTION_H
