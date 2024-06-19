#pragma once
#include "string"
#include "Dog.h"
#include "Repository.h"
#include "Service.h"
#include "UserService.h"

class Validation_exception: std::exception{
private:
    std::string message;
public:
    Validation_exception(std::string message);
    std::string getMessage() const;
};

class dogVali{
public:
    static void validate(const dog& d1);
};

class repoVali{
public:
    static void validateAdd(const Repository& repo, const dog& d1);
    static void validateDelete(const Repository& repo, const dog& d1);
    static void validateMod(const Repository& repo, const dog& d1);
};

void testAll();