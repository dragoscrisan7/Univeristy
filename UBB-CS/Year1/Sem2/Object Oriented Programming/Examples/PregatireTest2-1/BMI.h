//
// Created by Oana on 5/2/2022.
//

#pragma once
#include "Measurement.h"


class BMI: public Measurement {
private:
    double value;
public:
    ///CONSTRUCTORS
    BMI(){
        value=0;
        date="";
    }
    BMI(double v,std::string d){value=v;date=d;}
    BMI(const BMI& b){value=b.value;}

    ///ACTUAL CODE
    bool is_normal() const override{
        if (value >= 18.5 && value <= 25)
            return true;
        return false;
    }

    std::string to_string() const override{
        std::string aux = "Measurement: BMI: "+ std::to_string(value) +" date: "+ date + "\n" ;
        return aux;
    }



};
