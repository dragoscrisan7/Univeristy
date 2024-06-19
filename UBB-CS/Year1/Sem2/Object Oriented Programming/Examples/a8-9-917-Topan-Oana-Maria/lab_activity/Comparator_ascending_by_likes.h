//
// Created by Oana on 4/18/2022.
//

#pragma once

#include "lab_activity/Comparator.h"

class Comparator_ascending_by_likes : public Comparator<int>{
public:
    Comparator_ascending_by_likes(){};
    bool compare(int t1, int t2) const;

};

