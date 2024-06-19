#ifndef QUIZ_PARTICIPANTS_H
#define QUIZ_PARTICIPANTS_H
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Participants {
private:
    string name;
    int score;
public:
    Participants(const string &name);
    Participants();
    virtual ~Participants();

    friend ostream &operator<<(ostream &os, const Participants &participants);
    friend istream &operator>>(istream &is, Participants &participants);

    const string &getName() const;

    void setName(const string &name);

    int getScore() const;

    void setScore(int score);

    void raise_score(int score);
};


#endif //QUIZ_PARTICIPANTS_H
