#ifndef A8_9_DRAGOSCRISAN7_DOG_H
#define A8_9_DRAGOSCRISAN7_DOG_H
#include <iostream>

class dog{
private:
    std::string name;
    std::string breed;
    std::string photograph;
    int age;
public:
    dog(const std::string& name, const std::string& breed, const std::string& photograph, const int& age);
    dog();
    ~dog();

    [[nodiscard]] std::string get_name() const{return name;}
    [[nodiscard]] std::string get_breed() const{return breed;}
    [[nodiscard]] std::string get_photograph() const{return photograph;}
    [[nodiscard]] int get_age() const{return age;}

    void open() const;
    bool operator==(const dog &other);

    friend std::istream& operator>>(std::istream& is, dog& dog1);
    friend std::ostream& operator<<(std::ostream& os, dog& dog1);

    //function that returns a string containing all the information stored int the current class dog
    [[nodiscard]] std::string toString() const;
};

#endif //A8_9_DRAGOSCRISAN7_DOG_H
