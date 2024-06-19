//
// Created by Oana on 4/18/2022.
//

#pragma once

#include <string>
#include "lab_activity/Comparator.h"

class Comparator_descending_by_title : public Comparator<std::string>{
public:
    Comparator_descending_by_title(){};
    bool compare(std::string t1, std::string t2) const;
};

