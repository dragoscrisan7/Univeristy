//
// Created by Oana on 6/6/2022.
//

#pragma once
#include <string>
#include <ostream>

class Participant {
private:
    std::string name;
    int score;


public:
    Participant(const std::string &name, int score);
    Participant(const Participant& p);
    Participant();

    const std::string &getName() const;

    void setName(const std::string &name);

    int getScore() const;

    void setScore(int score);

    void upScore(int sc){
        score+=sc;
    }

    friend std::ostream &operator<<(std::ostream &os, const Participant &participant);

    friend std::istream &operator>>(std::istream &is, Participant &participant);

};


