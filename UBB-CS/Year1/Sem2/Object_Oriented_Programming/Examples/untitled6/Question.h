#pragma once
#include <ostream>
#include <string>
#include <vector>
using namespace std;

class Question {
private:
    int id, score;
    string text, correct_answer;
public:
    Question();
    Question(int id, const string &text, const string &correctAnswer, int score);
    Question(const Question& q);
    ~Question();

    int getId() const;

    void setId(int id);

    int getScore() const;

    void setScore(int score);

    const string &getText() const;

    void setText(const string &text);

    const string &getCorrectAnswer() const;

    void setCorrectAnswer(const string &correctAnswer);

    friend ostream &operator<<(ostream &os, const Question &question);
    friend istream &operator>>(istream &is, Question &question);

    bool operator==(const Question &rhs) const;
    bool operator!=(const Question &rhs) const;

};
