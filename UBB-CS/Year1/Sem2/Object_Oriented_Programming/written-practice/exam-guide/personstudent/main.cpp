#include <iostream>

class Person {
public:
    Person() { std::cout << "Person{}"; }
    virtual void print() = 0;
    virtual ~Person() { std::cout << "~Person()"; }
};

int main() {
    Person* p = new Person{};

    return 0;
}
