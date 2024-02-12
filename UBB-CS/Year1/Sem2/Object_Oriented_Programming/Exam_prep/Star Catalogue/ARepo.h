//
// Created by Dragos on 7/5/2022.
//

#ifndef STAR_CATALOGUE_AREPO_H
#define STAR_CATALOGUE_AREPO_H
#include "Astronomers.h"

class ARepo {
private:
    string file_name = "C:\\Users\\Dragos\\CLionProjects\\Star Catalogue\\Astronomers.txt";
    vector<Astronomers> arr;
public:
    ARepo();

    virtual ~ARepo();


    void read_from_file();
    void save_to_file();
    vector<Astronomers>& getAll();
};


#endif //STAR_CATALOGUE_AREPO_H
