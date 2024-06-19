//
// Created by Dragos on 6/27/2022.
//

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
    void removeObserver(Observer* o);
    void notify();
};


