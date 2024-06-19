#ifndef A5_6_DRAGOSCRISAN7_DOG_H
#define A5_6_DRAGOSCRISAN7_DOG_H
#include <iostream>

class dog{
private:
    std::string breed;
    std::string name;
    std::string photograph;
    int age;
public:
    //Constructor of the class dog
    dog(const std::string& breed, const std::string& name, const std::string& photograph, const int& age);
    //Default constructor of the class dog
    dog(){age = 0;}
    //Destructor of the class dog
    ~dog();

    //bool operator for the class dog
    bool operator==(const dog& other);

    //getter that returns the string breed
    std::string get_breed() const { return breed;}
    //getter that returns the string name
    std::string get_name() const { return name;}
    //getter that returns the string photograph
    std::string get_photograph() const { return photograph;}
    //getter that returns the int age
    int get_age() const { return age;}

    //function that returns a string containing all the information stored int the current class dog
    std::string toString() const;
};

#endif //A5_6_DRAGOSCRISAN7_DOG_H
