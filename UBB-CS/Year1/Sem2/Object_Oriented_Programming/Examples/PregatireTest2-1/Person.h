//
// Created by Oana on 5/2/2022.
//

#pragma once
#include "Measurement.h"
#include <vector>

class Person {
private:

    std::vector<Measurement*> measurements;
public:
    ///CONSTRUCTORS
    std::string name;
    Person(){name=""; measurements.clear();}
    Person(std::string n){name=n; measurements.clear();}

    //ACTUAL CODE
    void add_measurement(Measurement* m);
    std::vector<Measurement*> get_all_measurements();
    std::vector<Measurement*> get_measurements_by_month(int month);
    bool is_healthy(int month);
    std::vector<Measurement*> get_measurements_newer_than(std::string date);
    void write_to_file(std::string file_name, std::string date);
};


