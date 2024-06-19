#include "Service.h"
#include <fstream>

std::vector<Appliance *> Service::getAllAppliances() {
    return appliances;
}

void Service::addAppliance(Appliance *a) {
    this->appliances.push_back(a);
}

std::vector<Appliance *> Service::getAllWithConsumedElectricityLessThan(double maxElectricity) {
    std::vector<Appliance*> v;
    for(auto a:appliances){
        if(a->consumedElectricity() < maxElectricity)
            v.push_back(a);
    }
    return v;
}

void Service::writeToFile(std::string filename, double value) {
    std::ofstream f(filename);
    if(f.is_open()){
        for(auto a:appliances){
            if(a->consumedElectricity() > value)
                f<<a->toString();
        }
        f.close();
    }
}





