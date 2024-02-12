#include "Block.h"

bool Block::mustBeRestored() {
    double percentage =(occupiedApartments*1.0)/totalApartments;
    if(2022 - this->constructionYear > 40 && percentage>0.80)
        return true;
    else
        return false;
}

bool Block::canBeDemolished() {
    double percentage =(occupiedApartments*1.0)/totalApartments;
    if(percentage<0.05)
        return true;
    else
        return false;
}

std::string Block::toString() {
    return "Block: "+ this->address + ", " + std::to_string(this->constructionYear) + ", " + std::to_string(this->totalApartments) + ", " + std::to_string(this->occupiedApartments) + "\n";
}
