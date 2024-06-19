#ifndef A5_6_DRAGOSCRISAN7_REPOSITORY_H
#define A5_6_DRAGOSCRISAN7_REPOSITORY_H
#include "Dynamic_array.h"

class Repository
{
private:
    DynamicVector<dog>* dogs;
public:
    //Constructor for the Repository
    Repository(DynamicVector<dog>* dyn);
    //Default constructor for the Repository
    Repository() = default;
    //getter for the number of elements stored in the dynamic vector stored in the repository
    int getSize();
    //Function for getting a pointer to the vector stored in this class
    DynamicVector<dog>* getAllRepo();
    //Function for adding 10 classes dog into the vector prior to the program ui start
    void initialiseRepo();

    //Getter of the position of a class dog identified by its name
    int find(const std::string& name);
    //Function for adding a dog to the repo
    void addDog(const dog& d);
    //Function for deleting a dog from the repo
    void deleteDog(const std::string& name);
    //Function for modifying a dog from the repo, identified by its name
    void updateDog(const std::string& name, const dog& d1);
};

#endif //A5_6_DRAGOSCRISAN7_REPOSITORY_H
