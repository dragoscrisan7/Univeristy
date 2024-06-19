//
// Created by Oana on 5/2/2022.
//

#pragma once
#include "Building.h"
#include "Block.h"
#include "House.h"
#include <vector>



class Service {
private:
    std::vector<Building*> buildings;
public:
    Service(){
        buildings.clear();
    }

    void add_building(Building *b);

    std::vector<Building*> get_all_buildings();

    std::vector<Building*> get_all_to_be_restored();

    std::vector<Building*> get_all_to_be_demolished();

    void write_to_file(std::string file_name, std::vector<Building*> lots_of_buildings);

};
