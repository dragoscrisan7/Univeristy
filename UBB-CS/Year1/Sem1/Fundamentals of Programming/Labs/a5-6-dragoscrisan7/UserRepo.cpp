#include "UserRepo.h"

user_repo::user_repo(DynamicVector<dog>* adyn) {
    this->adopted = adyn;
}

int user_repo::getSize() {
    return this->adopted->getSize();
}

void user_repo::addDog(const dog &d) {
    this->adopted->add(d);
}

DynamicVector<dog> *user_repo::getAllAdopted() {
    return this->adopted;
}
