#pragma once
#include "Question.h"

class Repository {
private:
    vector<Question> arr;
    std::string file_name = "C:\\Users\\Dragos\\OneDrive\\Facultate\\Year1Sem2\\Object_Oriented_Programming\\Examples\\untitled6\\Questions.txt";

    void read_from_file();
    void save_to_file();
public:
    Repository();
    ~Repository();
    void add(const Question& q);
    int size();
    Question& operator[](int index);

    int get_index_for_id(int id);
    std::vector<Question> get_all_questions();
};

