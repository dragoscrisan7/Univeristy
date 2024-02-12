//
// Created by Dragos on 6/29/2022.
//

#include "Observer.h"

void Subject::add_observer(Observer* o) {
    observers.push_back(o);
}

void Subject::notify() {
    for(auto o:observers){
        o->update();
    }
}

Observer::~Observer() {

}
