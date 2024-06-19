#include "Repository.h"

using namespace std;

Repository::Repository(DynamicVector<dog> *dyn) {
    this->dogs = dyn;
}

void Repository::addDog(const dog& d) {
    this->dogs->add(d);
}
void Repository::deleteDog(const std::string& name) {
    auto i = find(name);
    if(i != -1)
        this->dogs->del(i);
    else
        throw std::invalid_argument("Dog not found");
}
int Repository::find(const std::string& name) {
    for(int i=0; i < dogs->getSize(); i++){
        if((*dogs)[i].get_name() == name)
            return i;
    }
    return -1;
}
void Repository::updateDog(const std::string& name, const dog& d1) {
    auto i = find(name);
    if(i != -1)
        this->dogs->update(i, d1);
    else
        throw std::invalid_argument("Dog not found");
}
void Repository::initialiseRepo() {
    dog dog1("German Shepherd", "Bond", "https://www.wowwow.ro/ciobanesc-german-caine/2145#",1);
    dog dog2("Husky", "Yoda", "https://www.wowwow.ro/husky-caine/2152", 5);
    dog dog3("Golden Retriever", "Murray", "https://www.wowwow.ro/golden-retriever-caine/2151", 3);
    dog dog4("Poodle", "Baby", "https://www.wowwow.ro/pudel-standard-%28caniche%29-caine/2163", 2);
    dog dog5("Husky", "Ice", "https://www.wowwow.ro/husky-caine/2152", 7);
    dog dog6("Samoyed", "Bear", "https://www.wowwow.ro/samoyed-caine/2298", 0);
    dog dog7("Husky", "Hudson", "https://www.wowwow.ro/husky-caine/2152", 10);
    dog dog8("Akita Inu", "Dash", "https://www.wowwow.ro/akita-inu-caine/2131", 3);
    dog dog9("Akita Inu", "Geo", "https://www.wowwow.ro/akita-inu-caine/2131", 6);
    dog dog10("Corgi", "Jedi", "https://www.wowwow.ro/welsh-corgi-pembroke-caine/2332", 1);
    this->dogs->add(dog1);
    this->dogs->add(dog2);
    this->dogs->add(dog3);
    this->dogs->add(dog4);
    this->dogs->add(dog5);
    this->dogs->add(dog6);
    this->dogs->add(dog7);
    this->dogs->add(dog8);
    this->dogs->add(dog9);
    this->dogs->add(dog10);
}
int Repository::getSize() {
    return this->dogs->getSize();
}
DynamicVector<dog>* Repository::getAllRepo() {
    return this->dogs;
}