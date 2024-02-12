//
// Created by Oana on 6/6/2022.
//

#pragma once

#include <string>
#include <ostream>

class Question {
private:
    int id;
    std::string text;
    std::string correct_answer;
    int score;

public:
    Question(int id_, std::string t, std::string ca, int sc);
    Question(const Question& q);
    Question();

    bool operator==(const Question &rhs) const;

    bool operator!=(const Question &rhs) const;

    int getId() const;

    const std::string &getText() const;

    const std::string &getCorrectAnswer() const;

    int getScore() const;

    friend std::ostream &operator<<(std::ostream &os, const Question &question);

    friend std::istream &operator>>(std::istream &is, Question &question);

    void setId(int id);

    void setText(const std::string &text);

    void setCorrectAnswer(const std::string &correctAnswer);

    void setScore(int score);

};
