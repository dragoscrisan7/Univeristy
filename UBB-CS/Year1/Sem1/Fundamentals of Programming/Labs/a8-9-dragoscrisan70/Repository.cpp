#include "Repository.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

Repository::Repository(const std::string &filename) {
    this->filename = filename;
    this->readFromFile();
}

dog Repository::findByNameAndBreed(const std::string &name,const std::string &breed) {
    auto it = find_if(dogs.begin(), dogs.end(), [name, breed](dog& d){return (d.get_name() == name && d.get_breed() == breed);});
    if (it == dogs.end())
        return dog{};
    else
        return *it;
}

void Repository::addDog(const dog& dog1) {
    this->dogs.push_back(dog1);
    this->writeToFile();
}

void Repository::delDog(const string &name, const string &breed) {
    auto it2 = find_if(this->dogs.begin(), this->dogs.end(),[name, breed](dog& d){return (d.get_name() == name && d.get_breed() == breed);});
    this->dogs.erase(it2);
    this->writeToFile();
}
void Repository::modDog(const string &name, const string &breed, const dog& dog1) {
    auto it2 = find_if(this->dogs.begin(), this->dogs.end(),[name, breed](dog& d){return (d.get_name() == name && d.get_breed() == breed);});
    (*it2) = dog1;
    this->writeToFile();
}

void Repository::readFromFile() {
    ifstream file(this->filename);

    if(!file.good())
        throw exception();

    if(!file.eof()) {
        dog d1;
        while (file >> d1)
            this->dogs.push_back(d1);
    }

    file.close();
}

void Repository::writeToFile(){
    ofstream file(this->filename);

    if(!file.is_open())
        throw exception();
    for(auto iter = this->dogs.begin(); iter < this->dogs.end()-1; iter++){
        file << *iter << "\n";
    }
    if(this->dogs.size()!=0)
        file << this->dogs.back();

    file.close();
}

int Repository::getSize() {
    return this->dogs.size();
}
