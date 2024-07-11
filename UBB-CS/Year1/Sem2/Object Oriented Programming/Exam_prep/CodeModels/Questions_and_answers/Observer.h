//
// Created by Dragos on 6/29/2022.
//

#ifndef QUESTIONS_AND_ANSWERS_OBSERVER_H
#define QUESTIONS_AND_ANSWERS_OBSERVER_H
#include <vector>
using namespace std;
class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer();
};

class Subject{
    vector<Observer*> observers;
public:
    void add_observer(Observer* o);
    void notify();
};


#endif //QUESTIONS_AND_ANSWERS_OBSERVER_H
