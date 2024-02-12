//
// Created by Oana on 5/2/2022.
//

#include "Service.h"
#include <fstream>

void Service::add_building(Building *b) {
    buildings.push_back(b);
}

std::vector<Building *> Service::get_all_buildings() {
    return buildings;
}

std::vector<Building*> Service::get_all_to_be_restored() {
    std::vector<Building*> aux;
    for (auto b: buildings)
        if ( (*b).must_be_restored())
            aux.push_back(b);
    return aux;
}

std::vector<Building*> Service::get_all_to_be_demolished() {
    std::vector<Building*> aux;
    for (auto b: buildings)
        if ( (*b).can_be_demolished())
            aux.push_back(b);
    return aux;
}

void Service::write_to_file(std::string file_name, std::vector<Building*> lots_of_buildings) {
    std::ofstream f(file_name);
    if (f.is_open())
    {
        for (auto b: lots_of_buildings)
            f<<(*b).to_string();
        f.close();
    }
}
