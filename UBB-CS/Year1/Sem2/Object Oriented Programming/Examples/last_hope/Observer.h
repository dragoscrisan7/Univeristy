#pragma once
#include <vector>

using namespace std;

class Observer {
public:
    virtual void populate() = 0;
};

class Subject {
private:
    vector<Observer*> observers;
public:
    void add(Observer* o) { observers.push_back(o); }
    void notify() {
        for (const auto &observer: observers)
            observer->populate();
    }
};