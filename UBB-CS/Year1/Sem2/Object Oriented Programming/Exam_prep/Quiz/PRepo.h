//
// Created by Dragos on 6/27/2022.
//

#ifndef QUIZ_PREPO_H
#define QUIZ_PREPO_H
#include "Participants.h"

class PRepo {
private:
    vector<Participants> arr;
    string file_name = "C:\\Users\\Dragos\\CLionProjects\\Quiz\\Participants.txt";
public:
    PRepo();
    virtual ~PRepo();

    void save_to_file();
    void read_from_file();

    vector<Participants>& getALL();
};


#endif //QUIZ_PREPO_H
