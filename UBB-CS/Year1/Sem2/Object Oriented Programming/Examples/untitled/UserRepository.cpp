#include "UserRepository.h"

UserRepo::UserRepo() = default;


UserRepo::UserRepo(std::vector<dog>& dogs) {
    this->adopted = dogs;
}

void UserRepo::addDog(const dog &d) {
    this->adopted.push_back(d);
    writeToFile();
}
