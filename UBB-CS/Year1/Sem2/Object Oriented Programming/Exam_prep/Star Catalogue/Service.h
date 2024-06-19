//
// Created by Dragos on 7/5/2022.
//

#ifndef STAR_CATALOGUE_SERVICE_H
#define STAR_CATALOGUE_SERVICE_H
#include "SRepo.h"
#include "Observer.h"

class Service : public Subject {
private:
    SRepo& srepo;
public:
    Service(SRepo &srepo);

    virtual ~Service();

    vector<Stars>& getAllStars();
    vector<Stars> getAllWithConst(string constellation);

    bool search(string& name);

    void add(string name, string constellation, int ra, int dec, int diameter);
};


#endif //STAR_CATALOGUE_SERVICE_H
