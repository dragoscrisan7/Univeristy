#pragma once
#include "Appliance.h"

class Refrigerator: public Appliance{
private:
    std::string electricityUsageClass;
    bool hasFreezer;
public:
    Refrigerator(){
        id = "";
        weight = 0;
        electricityUsageClass = "";
        hasFreezer = false;
    }
    Refrigerator(Refrigerator& r){
        id = r.id;
        weight = r.weight;
        electricityUsageClass = r.electricityUsageClass;
        hasFreezer = r.hasFreezer;
    }
    Refrigerator(std::string id, double w, std::string eluc, double hF){
        this->id = id;
        weight = w;
        electricityUsageClass = eluc;
        hasFreezer = hF;
    }



    double consumedElectricity() override;
    std::string toString() override;
};