//
// Created by Dragos on 7/5/2022.
//

#ifndef STAR_CATALOGUE_OBSERVER_H
#define STAR_CATALOGUE_OBSERVER_H

#pragma once
#include <vector>

class Observer
{
public:
    virtual void update() = 0;
    virtual ~Observer() {}
};

class Subject
{
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* o);
    void notify();
};



#endif //STAR_CATALOGUE_OBSERVER_H
