#ifndef A5_6_DRAGOSCRISAN7_SERVICE_H
#define A5_6_DRAGOSCRISAN7_SERVICE_H
#include "Repository.h"

class Service
{
private:
    Repository *repo;
public:
    //Constructor of the Service
    Service(Repository* r);
    //Function for deleting a dog identified by its name from the service
    void delDoggo(const std::string& name);
    //Function to modify a dog identified by its name from the service
    void updateDoggo(const std::string& name, const std::string& name2, const std::string& breed2, const std::string& photograph2, int age2);
    //Function for getting a pointer to the repository stored in this class
    Repository* getRepo();

    //Function for adding a dog to the service
    void addDoggo(const std::string &name, const std::string &breed, const std::string &photograph, int age);
};

#endif //A5_6_DRAGOSCRISAN7_SERVICE_H
