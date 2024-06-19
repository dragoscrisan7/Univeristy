//
// Created by kamui on 08.06.2022.
//

#ifndef E917_PATRULESCU_RONALD_SANDRINO_OBSERVER_H
#define E917_PATRULESCU_RONALD_SANDRINO_OBSERVER_H
#include <vector>

using namespace std;

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    vector<Observer*> observers;
public:
    void add(Observer* o) { observers.push_back(o); }
    void notify() {
        for (const auto &observer: observers)
            observer->update();
    }
};


#endif //E917_PATRULESCU_RONALD_SANDRINO_OBSERVER_H
