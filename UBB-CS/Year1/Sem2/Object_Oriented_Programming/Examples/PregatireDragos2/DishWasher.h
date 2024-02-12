#pragma once
#include "Appliance.h"

class DishWasher: public Appliance{
private:
    double washingCydeLength;
    double consumedElectricityForOneHour;
public:
    DishWasher(){
        id = "";
        weight = 0;
        washingCydeLength = 0;
        consumedElectricityForOneHour = 0;
    }
    DishWasher(DishWasher& dw){
        id = dw.id;
        weight = dw.weight;
        washingCydeLength = dw.washingCydeLength;
        consumedElectricityForOneHour = dw.consumedElectricityForOneHour;
    }
    DishWasher(std::string id, double w, double wcl, double cefoh){
        this->id = id;
        weight = w;
        washingCydeLength = wcl;
        consumedElectricityForOneHour = cefoh;
    }


    double consumedElectricity() override;
    std::string toString() override;
};
