#ifndef QUIZ_QUESTIONS_H
#define QUIZ_QUESTIONS_H
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Questions {
private:
    int id, score;
    string text, correct_answer;
public:
    Questions(int id, int score, const string &text, const string &correctAnswer);
    Questions();
    virtual ~Questions();

    friend ostream &operator<<(ostream &os, const Questions &questions);
    friend istream &operator>>(istream &is, Questions &questions);

    int getId() const;

    void setId(int id);

    int getScore() const;

    void setScore(int score);

    const string &getText() const;

    void setText(const string &text);

    const string &getCorrectAnswer() const;

    void setCorrectAnswer(const string &correctAnswer);
};


#endif //QUIZ_QUESTIONS_H
