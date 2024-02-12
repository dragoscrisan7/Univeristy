#include "UserService.h"
#include <algorithm>

using namespace std;

UserService::UserService(UserRepo *urepo, Repository *repo) {
    this->urepo = urepo;
    this->repo = repo;
}

UserRepo *UserService::getRepo() {
    return this->urepo;
}

void UserService::add_adopted_dog(const std::string &name, const std::string &breed, const std::string &photograph,
                                  int age) {
    dog dog1(name, breed, photograph, age);
    this->urepo->addDog(dog1);
    this->repo->delDog(name, breed);
}

int UserService::get_all_filtered(std::vector<dog> &valid_dogs, const std::string &breed, int age) {
    const auto &list = repo->getDog();
    copy_if(list.begin(), list.end(), back_inserter(valid_dogs),[breed, age](const dog &dog1){return (dog1.get_breed() == breed && dog1.get_age()<age);});
    return valid_dogs.size();

}

std::string &UserService::getFileService() {
    return this->urepo->getFileName();
}

UserService::UserService(Repository *repo) {
    this->repo = repo;
}

void UserService::repoType(int fileType) {
    if (fileType == 1) {
        std::vector<dog> userVector;
        std::string userFile = R"(C:\Users\Dragos\OneDrive\Facultate\Year1Sem2\Object_Oriented_Programming\Examples\untitled\AdoptedList.csv)";
        auto * repo = new csvfile{ userVector, userFile};
        this->urepo = repo;
    }else if (fileType == 2) {
        std::vector<dog> userVector ;
        std::string userFile = R"(C:\Users\Dragos\OneDrive\Facultate\Year1Sem2\Object_Oriented_Programming\Examples\untitled\AdoptedList.html)";
        auto * repo = new htmlfile{userVector, userFile};
        this->urepo = repo;
    }
}

void UserService::openFile() {
    this->urepo->open();
}


