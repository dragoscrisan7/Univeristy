//
// Created by Dragos on 7/5/2022.
//

#ifndef STAR_CATALOGUE_SREPO_H
#define STAR_CATALOGUE_SREPO_H
#include "Stars.h"
#include <algorithm>

class SRepo {
private:
    vector<Stars> arr;
    string file_name = "C:\\Users\\Dragos\\CLionProjects\\Star Catalogue\\Stars.txt";
public:
    SRepo();

    virtual ~SRepo();

    void read_from_file();
    void save_to_file();
    vector<Stars>& getAll();

    void add(Stars& s);
};


#endif //STAR_CATALOGUE_SREPO_H
