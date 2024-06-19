#include "Refrigerator.h"

std::string Refrigerator::toString() {
    return "Refrigerator: " + id + ", " + std::to_string(weight) + ", " + electricityUsageClass + ", has freezer: " + std::to_string(hasFreezer) + "\n";
}

double Refrigerator::consumedElectricity() {
    double x;
    if(electricityUsageClass == "A")
        x = 3;
    else if(electricityUsageClass == "A++")
        x = 2;
    else
        x= 2.5;
    x = x * 30;
    if(hasFreezer)
        x = x + 20;
    return x;
}

