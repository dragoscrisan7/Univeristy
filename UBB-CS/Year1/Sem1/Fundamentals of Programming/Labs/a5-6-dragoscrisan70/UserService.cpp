#include "UserService.h"

UserService::UserService(user_repo *urepo, Repository* repo) {
    this->urepo = urepo;
    this->repo = repo;
}

user_repo *UserService::getRepo() {
    return this->urepo;
}

void UserService::add_adopted_dog(const std::string& name, const std::string &breed, const std::string &photograph,
                                  int age) {
    dog dog1(breed, name, photograph, age);
    this->urepo->addDog(dog1);
}

int UserService::get_all_filtered(dog *valid_dogs, const std::string &breed, int age) {
    int cont = 0;
    int length = this->repo->getSize();
    for (int i = 0; i < length; i++)
    {
        dog dog1((*this->repo->getAllRepo())[i]);
        if(dog1.get_breed() == breed && dog1.get_age()<age){
            valid_dogs[cont] = dog1;
            cont++;
        }
    }
    return cont;
}
