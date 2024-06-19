//
// Created by Oana on 4/18/2022.
//

#pragma once
#include <vector>
#include <algorithm>

template <typename TElement>
class Comparator {
public:
    virtual bool compare(TElement t1, TElement t2) const = 0;
};

template <typename TElement>
void sort_the_vector(std::vector<TElement> v, Comparator<TElement>* c)
{
    std::sort(v.begin(), v.end(), c->compare);
}