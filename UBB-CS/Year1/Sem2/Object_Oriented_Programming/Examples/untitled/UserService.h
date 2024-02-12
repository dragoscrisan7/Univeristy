#pragma once
#include "UserRepository.h"
#include "Repository.h"
#include "CSVfile.h"
#include "HTMLfile.h"

class UserService{
private:
    UserRepo* urepo;
    Repository* repo;
public:
    //Constructor of the user service
    explicit UserService(Repository* repo);
    explicit UserService(UserRepo *urepo, Repository* repo);



    //Function for adding a dog
    void add_adopted_dog(const std::string& name, const std::string &breed, const std::string &photograph, int age);
    //Function that adds to the parameter valid dogs the dogs that have the given breed and are under the given age
    //returns the number of dogs added
    int get_all_filtered(std::vector<dog>& valid_dogs, const std::string& breed, int age);

    void repoType(int file);
    std::string& getFileService();
    void openFile();

    //Function that returns a pointer to the repository stored in the urepo from this service
    UserRepo* getRepo();
};
