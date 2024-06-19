#pragma once
#include "UserService.h"

class htmlfile: public UserRepo{
public:
    htmlfile(std::vector<dog> &adopted, std::string& filename);

    int getSize() override;
    void writeToFile() override;
    std::string& getFileName() override;
    std::vector<dog> getDog() override;
    void open() override;

    ~htmlfile() = default;
};