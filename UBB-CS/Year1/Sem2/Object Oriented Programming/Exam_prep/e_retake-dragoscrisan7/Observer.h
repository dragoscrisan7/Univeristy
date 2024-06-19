//
// Created by Dragos on 7/6/2022.
//

#ifndef UEXAM_OBSERVER_H
#define UEXAM_OBSERVER_H


#pragma once
#include <vector>

class Observer
{
public:
    virtual void update() = 0;
    virtual ~Observer() {}
};

class Observable
{
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* o);
    void notify_all_observables();
};



#endif //UEXAM_OBSERVER_H
