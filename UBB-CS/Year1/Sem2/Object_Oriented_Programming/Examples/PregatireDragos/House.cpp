#include "House.h"

bool House::mustBeRestored() {
    if(2022 - this->constructionYear > 100)
        return true;
    else
        return false;
}

bool House::canBeDemolished() {
    return !isHistorical;
}

std::string House::toString() {
    return "House: "+ this->address + ", " + std::to_string(this->constructionYear) + ", is historical: " + std::to_string(this->isHistorical) + "\n";
}
