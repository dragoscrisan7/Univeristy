//
// Created by Dragos on 7/6/2022.
//

#ifndef UEXAM_TREPO_H
#define UEXAM_TREPO_H
#include "Topics.h"
#include <algorithm>

class TRepo {
private:
    string file_name = "C:\\Users\\Dragos\\CLionProjects\\uExam\\Topics.txt";
    vector<Topics> arr;
public:
    TRepo();

    virtual ~TRepo();

    void read_from_file();
    void save_to_file();
    vector<Topics>& getAll();
    vector<Topics> getAllForUser(string& user);
    void add_subscriber(string& topic_name, string& name);
};


#endif //UEXAM_TREPO_H
