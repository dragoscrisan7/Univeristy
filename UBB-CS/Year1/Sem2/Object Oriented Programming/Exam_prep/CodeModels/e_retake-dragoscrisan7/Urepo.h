//
// Created by Dragos on 7/6/2022.
//

#ifndef UEXAM_UREPO_H
#define UEXAM_UREPO_H
#include "Users.h"

class Urepo {
private:
    string file_name = "C:\\Users\\Dragos\\CLionProjects\\uExam\\Users.txt";
    vector<Users> arr;
public:
    Urepo();

    virtual ~Urepo();

    void read_from_file();
    void save_to_file();

    vector<Users>& get_all();
};


#endif //UEXAM_UREPO_H
