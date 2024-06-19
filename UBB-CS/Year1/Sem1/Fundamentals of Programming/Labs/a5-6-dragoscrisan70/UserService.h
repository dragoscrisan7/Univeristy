#ifndef A5_6_DRAGOSCRISAN7_USERSERVICE_H
#define A5_6_DRAGOSCRISAN7_USERSERVICE_H
#include "UserRepo.h"
#include "Repository.h"

class UserService
{
private:
    user_repo* urepo;
    Repository* repo;
public:
    //Constructor of the user service
    UserService(user_repo *urepo, Repository* repo);

    //Function for adding a dog
    void add_adopted_dog(const std::string& name, const std::string &breed, const std::string &photograph, int age);
    //Function that adds to the parameter valid dogs the dogs that have the given breed and are under the given age
    //returns the number of dogs added
    int get_all_filtered(dog * valid_dogs, const std::string& breed, int age);

    //Function that returns a pointer to the repository stored in the urepo from this service
    user_repo* getRepo();
};

#endif //A5_6_DRAGOSCRISAN7_USERSERVICE_H
