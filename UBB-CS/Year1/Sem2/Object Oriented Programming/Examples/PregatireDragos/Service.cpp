#include "Service.h"
#include <fstream>

void Service::addBuilding(Building *b) {
    this->buildings.push_back(b);
}

std::vector<Building *> Service::getAllBuildings() {
    return buildings;
}

std::vector<Building *> Service::getAllToBeRestored() {
    std::vector<Building*> v;
    for(auto b: buildings){
        if(b->mustBeRestored())
            v.push_back(b);
    }
    return v;
}

std::vector<Building *> Service::getAllToBeDemolished() {
    std::vector<Building*> v;
    for(auto b: buildings){
        if(b->canBeDemolished())
            v.push_back(b);
    }
    return v;
}

void Service::writeToFile(std::string filename, std::vector<Building *> buildings) {
    std::ofstream fout(filename);
    if(fout.is_open()){
        for(auto b: buildings)
            fout<<b->toString();
        fout.close();
    }
}

