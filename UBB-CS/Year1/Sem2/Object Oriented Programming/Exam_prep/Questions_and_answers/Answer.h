//
// Created by Dragos on 6/28/2022.
//

#ifndef QUESTIONS_AND_ANSWERS_ANSWER_H
#define QUESTIONS_AND_ANSWERS_ANSWER_H
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Answer {
private:
    int id, qid;
    string text, user_name;
    int votes;
public:
    Answer(int id, int qid, const string &text, const string &userName, int votes);

    Answer();

    virtual ~Answer();

    int getId() const;

    void setId(int id);

    int getQid() const;

    void setQid(int qid);

    const string &getText() const;

    void setText(const string &text);

    const string &getUserName() const;

    void setUserName(const string &userName);

    int getVotes() const;

    void setVotes(int votes);

    friend ostream &operator<<(ostream &os, const Answer &answer);
    friend istream &operator>>(istream &is, Answer &answer);
};

#endif //QUESTIONS_AND_ANSWERS_ANSWER_H
