#include "DishWasher.h"

std::string DishWasher::toString() {
    return "Refrigerator: " + id + ", " + std::to_string(weight) + ", " + std::to_string(washingCydeLength) + ", " + std::to_string(consumedElectricityForOneHour) + "\n";
}

double DishWasher::consumedElectricity() {
    double x;
    x = consumedElectricityForOneHour * washingCydeLength;
    x = x * 20;
    return x;
}

