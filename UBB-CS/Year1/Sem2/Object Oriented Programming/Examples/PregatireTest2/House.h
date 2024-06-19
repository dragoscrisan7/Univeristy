//
// Created by Oana on 5/2/2022.
//

#pragma once
#include "Building.h"

class House : public Building{
private:
    bool is_historical;
public:
    ///Constructors
    House(){
        address="";
        construction_year=0;
        is_historical=false;
    }

    House(const House& h)
    {
        this->address = h.address;
        this->construction_year = h.construction_year;
        this->is_historical = h.is_historical;
    }

    House(std::string addr, int constr, bool hist)
    {
        address=addr;
        construction_year=constr;
        is_historical=hist;
    }

    bool must_be_restored()const override{
        if (2022 - construction_year > 100)
            return true;
        return false;
    }
    bool can_be_demolished() const override{
        if (is_historical==false)
            return true;
        return false;
    }
    std::string to_string() const override{
        std::string aux = "House: address: "+ address +" construction year: "+ std::to_string(construction_year);
        if (is_historical)
            aux += " is historical.\n";
        else
            aux += " isn't historical.\n";
        return aux;
    }

};

