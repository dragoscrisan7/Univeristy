#include "Dog.h"
#include <Windows.h>
#include <shellapi.h>
///#include <Utils.h>

using namespace std;

dog::dog(const string &name, const string &breed, const string &photograph, const int &age) {
    this->breed = breed;
    this->name = name;
    this->photograph = photograph;
    this->age = age;
}
dog::dog() : breed(""), name(""), photograph(""), age(0){}
dog::~dog() = default;

void dog::open() const{
    ShellExecuteA(nullptr, nullptr, "chrome.exe", this->get_photograph().c_str(), nullptr, SW_SHOWMAXIMIZED);
}

std::istream & operator>>(std::istream& is, dog& dog1) {
    if (is.eof())
        is.setstate(ios_base::failbit);
    else{
        std::string age;
        getline(is,dog1.name,',');
        getline(is,dog1.breed,',');
        getline(is,age,',');
        try{
            dog1.age = stoi(age);
        }
        catch (...){}
        getline(is,dog1.photograph,'\n');
    }
    return is;
}

std::ostream & operator<<(ostream &os, dog &dog1) {
    os << dog1.name << "," << dog1.breed << "," << dog1.age << "," << dog1.photograph;
    return os;
}

std::string dog::toString() const {
    auto str_age = std::to_string(this->age);
    return "Breed: " + this->breed + " | Name: " + this->name + " | Age: " + str_age + " | Photograph link: " +
           this->photograph;
}

bool dog::operator==(const dog &other) {
    return (this->name==other.name && this->breed==other.breed && this->photograph == other.photograph && this->age == other.age);
}

