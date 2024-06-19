#pragma once
#include "Dog.h"
#include <vector>
#include <windows.h>

class UserRepo{
protected:
    std::vector<dog> adopted;
    std::string userfilename;
public:
    //Constructor of the user repository
    UserRepo();
    explicit UserRepo(std::vector<dog> &dogs);
    //Getter for the number of elements in the vector of the repo
    virtual int getSize() = 0;

    //Function for adding a dog to the user repo
    void addDog(const dog& d);

    virtual void writeToFile() = 0;

    virtual std::string& getFileName() = 0;

    virtual std::vector<dog> getDog() = 0;

    virtual void open() = 0;

    ~UserRepo() = default;
};
