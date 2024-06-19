#include "Dog.h"

dog::dog(const std::string& breed, const std::string& name, const std::string& photograph, const int& age)
{
    this->name = name;
    this->breed = breed;
    this->photograph = photograph;
    this->age = age;
}

dog::~dog() = default;

std::string dog::toString() const {
    auto str_age = std::to_string(this->age);
    return "Breed: " + this->breed + " | Name: " + this->name + " | Age: " + str_age + " | Photograph link: " +
           this->photograph;
}

bool dog::operator==(const dog &other) {
    return (age == other.age && name == other.name && photograph == other.photograph && breed == other.breed);
}
