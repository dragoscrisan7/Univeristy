#pragma once
#include "UserRepository.h"
class csvfile: public UserRepo{
public:
    csvfile(std::vector<dog> &adopted, std::string& filename);

    int getSize() override;
    void writeToFile() override;
    std::string& getFileName() override;
    std::vector<dog> getDog() override;
    void open() override;

    ~csvfile();
};
