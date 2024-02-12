//
// Created by Oana on 6/6/2022.
//

#pragma once
#include "Question.h"
#include <vector>
#include <string>

class QuestionRepo {
private:
    std::vector<Question> arr;
    std::string file_name = "C:/Users/Oana/CLionProjects/practice_for_exam/quiz.txt";

    void read_from_file();
    void save_to_file();
public:
    QuestionRepo();
    void add(const Question& q);
    int size();
    Question& operator[](int index);
    ~QuestionRepo();

    int get_index_for_id(int id);
    std::vector<Question> get_all_questions();




};


