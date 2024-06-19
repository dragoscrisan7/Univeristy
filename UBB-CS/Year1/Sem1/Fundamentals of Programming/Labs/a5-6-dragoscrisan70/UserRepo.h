#ifndef A5_6_DRAGOSCRISAN7_USERREPO_H
#define A5_6_DRAGOSCRISAN7_USERREPO_H
#include "Dynamic_array.h"

class user_repo
{
private:
    DynamicVector<dog>* adopted;
public:
    //Constructor of the user repository
    user_repo(DynamicVector<dog>* adyn);
    //Getter for the number of elements in the vector of the repo
    int getSize();

    //Function for adding a dog to the user repo
    void addDog(const dog& d);
    //Function that returns a pointer to the vector stored in this repo
    DynamicVector<dog>* getAllAdopted();
};

#endif //A5_6_DRAGOSCRISAN7_USERREPO_H
