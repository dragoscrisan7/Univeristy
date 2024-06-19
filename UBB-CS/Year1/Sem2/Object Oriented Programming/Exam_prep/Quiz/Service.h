//
// Created by Dragos on 6/27/2022.
//

#ifndef QUIZ_SERVICE_H
#define QUIZ_SERVICE_H
#include "PRepo.h"
#include "QRepo.h"
#include <algorithm>
#include <exception>
#include "Observer.h"
class Service: public Subject {
private:
    QRepo& qr;
public:
    Service(QRepo &qr);
    ~Service();

    void add(int id, string text, string correct_answer, int score);
    int answer(int id, string answer);

    vector<Questions> sorted_by_id();
    vector<Questions> sorted_by_score();
};


#endif //QUIZ_SERVICE_H
