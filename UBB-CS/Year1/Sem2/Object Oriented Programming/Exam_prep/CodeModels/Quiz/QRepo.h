//
// Created by Dragos on 6/27/2022.
//

#ifndef QUIZ_QREPO_H
#define QUIZ_QREPO_H
#include "Questions.h"
#include <fstream>

class QRepo {
private:
    vector<Questions> arr;
    string file_name = "C:\\Users\\Dragos\\CLionProjects\\Quiz\\Questions.txt";
public:
    QRepo();
    virtual ~QRepo();

    void read_from_file();
    void save_to_file();

    void add_question(Questions& q);

    int answer_question(int id, string &answer);

    Questions& operator[](int index);
    int find_by_id(int id);
    vector<Questions> getALL();
};


#endif //QUIZ_QREPO_H
