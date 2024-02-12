#pragma once
#include "Building.h"

class House: public Building{
private:
    bool isHistorical;
public:
    ///Constructors
    House(){
        address = "";
        constructionYear = 0;
        isHistorical = false;
    }
    House(const House& h){
        this->address = h.address;
        this->constructionYear = h.constructionYear;
        this->isHistorical = h.isHistorical;
    }
    House(std::string a, int cY, bool ih){
        this->address = a;
        this->constructionYear = cY;
        this->isHistorical = ih;
    }

    bool mustBeRestored() override;
    bool canBeDemolished() override;
    std::string toString() override;
};