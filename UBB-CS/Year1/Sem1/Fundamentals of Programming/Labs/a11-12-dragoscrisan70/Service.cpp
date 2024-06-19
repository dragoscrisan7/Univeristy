#include "Service.h"

Service::Service(Repository* r) {
    this->repo = r;
}

void Service::delDoggo(const std::string &name, const std::string &breed) {
    auto dog1 = repo->findByNameAndBreed(name,breed);
    try{
        dogVali::validate(dog1);
    }
    catch(Validation_exception& e){
        std::cout<<e.getMessage()<<std::endl;
        return;
    }
    try{
        repoVali::validateDelete((*repo),dog1);
    }
    catch(Validation_exception& e){
        std::cout<<e.getMessage()<<std::endl;
        return;
    }
    repo->delDog(name, breed);
}

void Service::updateDoggo(const std::string &name, const std::string &breed, const std::string &name2, const std::string &breed2,
                          const std::string &photograph2, int age2) {
    auto dog1 = repo->findByNameAndBreed(name,breed);
    try{
        dogVali::validate(dog1);
    }
    catch(Validation_exception& e){
        std::cout<<e.getMessage()<<std::endl;
        return;
    }
    dog dog2(name2,breed2,photograph2, age2);
    try{
        repoVali::validateMod((*repo),dog1);
    }
    catch(Validation_exception& e){
        std::cout<<e.getMessage()<<std::endl;
        return;
    }

    this->repo->modDog(name,breed,dog2);
}

void Service::addDoggo(const std::string &name, const std::string &breed, const std::string &photograph, int age) {
    dog dog1(name,breed,photograph,age);
    try{
        dogVali::validate(dog1);
    }
    catch(Validation_exception& e){
        std::cout<<e.getMessage()<<std::endl;
    }
    try{
        repoVali::validateAdd((*repo),dog1);
    }
    catch(Validation_exception& e){
        std::cout<<e.getMessage()<<std::endl;
    }
    this->repo->addDog(dog1);
}

Repository *Service::getRepo() {
    return this->repo;
}

