//
// Created by Oana on 6/6/2022.
//

#include "QuestionRepo.h"
#include <fstream>

void QuestionRepo::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Question q;
        f>> q;
        this->arr.push_back(q);
    }
    f.close();

}

void QuestionRepo::save_to_file() {
    std::ofstream f(file_name);
    f.clear();
    for(const auto& q:arr){
        f<<q<<"\n";
    }
    f.close();
}

QuestionRepo::QuestionRepo() {
    this->read_from_file();
}

void QuestionRepo::add(const Question& q) {
    arr.push_back(q);
}

QuestionRepo::~QuestionRepo() {
    this->save_to_file();
}

int QuestionRepo::size() {
    return arr.size();
}

Question &QuestionRepo::operator[](int index) {
    if(index<0 || index>=this->size())
        throw "Bad index!";
    return arr[index];
}

int QuestionRepo::get_index_for_id(int id) {
    for(int i=0;i<this->size();i++)
        if(this->arr[i].getId()==id)
            return i;
    return -1;
}

std::vector<Question> QuestionRepo::get_all_questions() {
    return arr;
}

