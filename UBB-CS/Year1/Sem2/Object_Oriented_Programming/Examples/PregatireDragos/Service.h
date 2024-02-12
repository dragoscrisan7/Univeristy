#pragma once
#include "Building.h"
#include "House.h"
#include "Block.h"
#include <vector>

class Service{
private:
    std::vector<Building*> buildings;
public:
    void addBuilding(Building* b);
    std::vector<Building*> getAllBuildings();
    std::vector<Building*> getAllToBeRestored();
    std::vector<Building*> getAllToBeDemolished();
    void writeToFile(std::string filename,std::vector<Building*> buildings);
};
