#pragma once
#include "Dog.h"
#include <vector>
#include <exception>

class Repository{
private:
    std::vector<dog> dogs;
    std::string filename;
public:
    Repository(const std::string& filename);
    Repository() = default;

    void addDog(const dog& dog1);
    void delDog(const std::string& name, const std::string& breed);
    void modDog(const std::string& name, const std::string& breed, const dog& dog1);

    dog findByNameAndBreed(const std::string& name,const std::string& breed);
    int getSize();

    std::vector<dog> getDog() const{return dogs;}
private:
    void readFromFile();
    void writeToFile();
};