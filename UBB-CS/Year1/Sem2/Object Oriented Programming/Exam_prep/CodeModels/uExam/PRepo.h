//
// Created by Dragos on 7/6/2022.
//

#ifndef UEXAM_PREPO_H
#define UEXAM_PREPO_H
#include "Posts.h"

class PRepo {
private:
    string file_name = "C:\\Users\\Dragos\\CLionProjects\\uExam\\Posts.txt";
    vector<Posts> arr;
public:
    PRepo();

    virtual ~PRepo();

    void read_from_file();
    void save_to_file();
    vector<Posts>& getAll();

    void add(Posts& p);
    void modify(int id, string& text);
};


#endif //UEXAM_PREPO_H
