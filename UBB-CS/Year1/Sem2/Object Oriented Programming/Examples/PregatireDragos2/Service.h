#pragma once
#include "Appliance.h"
#include "Refrigerator.h"
#include "DishWasher.h"
#include <vector>

class Service{
private:
    std::vector<Appliance*> appliances;
public:
    void addAppliance(Appliance* a);
    std::vector<Appliance*> getAllAppliances();
    std::vector<Appliance*> getAllWithConsumedElectricityLessThan(double maxElectricity);
    void writeToFile(std::string filename, double value);
};
