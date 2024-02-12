//
// Created by Dragos on 7/5/2022.
//

#include "Service.h"

Service::Service(SRepo &srepo) : srepo(srepo) {}

Service::~Service() {

}

vector<Stars>& Service::getAllStars() {
    return srepo.getAll();
}

vector<Stars> Service::getAllWithConst(string constellation){
    vector<Stars> new_arr;
    for(auto s:srepo.getAll()){
        if(s.getConstellation() == constellation){
            new_arr.push_back(s);
        }
    }
    return new_arr;
}

void Service::add(string name, string constellation, int ra, int dec, int diameter) {
    Stars s(name, constellation, ra, dec, diameter);
    srepo.add(s);
    notify();
}

bool Service::search(string& name) {
    for(auto s:srepo.getAll()){
        if(s.getName() == name)
            return true;
    }
    return false;
}

