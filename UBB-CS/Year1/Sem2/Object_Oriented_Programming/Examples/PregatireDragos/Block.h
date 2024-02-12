#pragma once
#include "Building.h"

class Block: public Building{
private:
    int totalApartments;
    int occupiedApartments;
public:
    Block(){
        address = "";
        constructionYear = 0;
        totalApartments = 0;
        occupiedApartments = 0;
    }
    Block(const Block& b){
        address = b.address;
        constructionYear = b.constructionYear;
        totalApartments = b.totalApartments;
        occupiedApartments = b.occupiedApartments;
    }
    Block(std::string a, int cY, int tA, int oA){
        address = a;
        constructionYear = cY;
        totalApartments = tA;
        occupiedApartments = oA;
    }

    bool mustBeRestored() override;
    bool canBeDemolished() override;
    std::string toString() override;
};

