//
// Created by Oana on 5/2/2022.
//

#pragma once

#include "Building.h"

class Block:public Building {
private:
    int total_apartments;
    int occupied_apartments;
public:
    ///CONSTRUCTORS
    Block(){
        address = "";
        construction_year = 0;
        total_apartments = 0;
        occupied_apartments = 0;
    }
    Block(std::string address_, int construction, int total, int occupied){
        address=address_;
        construction_year=construction;
        total_apartments=total;
        occupied_apartments=occupied;
    }
    Block(const Block& b)
    {
        this->address=b.address;
        this->construction_year= b.construction_year;
        this->total_apartments = b.total_apartments;
        this->occupied_apartments = b.occupied_apartments;
    }

    bool must_be_restored() const override{
        int life = 2022-construction_year;
        double percentage = (occupied_apartments*1.0)/total_apartments;
        if ((life > 40) && (percentage > 0.80))
            return true;
        return false;
    }

    bool can_be_demolished() const override{
        if ((occupied_apartments*1.0)/total_apartments < 0.05)
            return true;
        return false;
    }


    std::string to_string() const override{
        std::string aux = "Block of apartments: address: " + address + " construction year:" + std::to_string(construction_year);
        aux += " total apartments: " + std::to_string(total_apartments) + " occupied apartments: " + std::to_string(occupied_apartments) + "\n";
        return aux;
    }

};


