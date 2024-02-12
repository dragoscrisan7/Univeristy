//
// Created by Oana on 5/2/2022.
//

#pragma once
#include "Measurement.h"


class BP: public Measurement {
private:
    int systolic_value;
    int diastolic_value;
public:
    ///CONSTRUCTORS
    BP(){systolic_value=0;diastolic_value=0;date="";}
    BP(int s, int d, std::string dat){systolic_value=s; diastolic_value=d;date=dat;}
    BP(const BP& b){systolic_value=b.systolic_value;diastolic_value=b.diastolic_value;date=b.date;}

    ///ACTUAL CODE

    bool is_normal() const override
    {
        if ((systolic_value<=119) && (systolic_value>=90) && (diastolic_value<=79) && (diastolic_value>=60))
            return true;
        return false;
    }

    std::string to_string() const override{
        std::string aux = "Measurement: BP: systolic: "+std::to_string(systolic_value) +" diastolic: "+ std::to_string(diastolic_value) +" date: "+date+"\n";
        return aux;
    }

};

