//
// Created by Oana on 5/2/2022.
//

#include "Person.h"
#include <fstream>

void Person::add_measurement(Measurement *m) {
    measurements.push_back(m);
}

std::vector<Measurement *> Person::get_all_measurements() {
    return measurements;
}

std::vector<Measurement *> Person::get_measurements_by_month(int month) {
    std::vector<Measurement*> by_month;
    for (auto m: measurements)
    {
        std::string aux = m->date.substr(5,2);
        int month_check=std::stoi(aux);
        if (month_check==month)
            by_month.push_back(m);
    }
    return by_month;
}

bool Person::is_healthy(int month) {
    if (month>1)
    {
        std::vector<Measurement*> previous_month = get_measurements_by_month(month-1);
        for (auto m: previous_month)
        {
            if (m->is_normal()==false)
                return false;
        }
    }
    std::vector<Measurement*> current_month = get_measurements_by_month(month);
    for(auto m: current_month)
        if (m->is_normal()==false)
            return false;
    return true;
}

std::vector<Measurement *> Person::get_measurements_newer_than(std::string date) {
    std::vector<Measurement*> newer_than;
    for(auto m: measurements)
    {
        if (date<m->date)
            newer_than.push_back(m);
    }
    return newer_than;
}

void Person::write_to_file(std::string file_name, std::string date) {
    std::ofstream f(file_name);
    if (f.is_open())
    {
        std::vector<Measurement*> to_write = get_measurements_newer_than(date);
        for (auto m: to_write)
            f<<m->to_string();
        f.close();
    }

}
