#include "Service.h"

void Service::addDoggo(const std::string& name, const std::string& breed, const std::string& photograph, int age)
{
    dog d(breed, name, photograph, age);
    repo->addDog(d);
}
void Service::delDoggo(const std::string& name)
{
    try{
        repo->deleteDog(name);
    }
    catch(std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
    }
}
void Service::updateDoggo(const std::string& name, const std::string& name2, const std::string& breed2, const std::string& photograph2, int age2)
{
    dog d2(breed2, name2, photograph2, age2);
    try {
        repo->updateDog(name, d2);
    }
    catch(std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
    }
}
Repository* Service::getRepo(){
    return this->repo;
}

Service::Service(Repository *r) {
    this->repo = r;
    repo->initialiseRepo();
}
