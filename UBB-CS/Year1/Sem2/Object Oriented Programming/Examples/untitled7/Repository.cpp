#include "Repository.h"
#include <fstream>

void Repository::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Question q;
        f>> q;
        this->arr.push_back(q);
    }
    f.close();
}

void Repository::save_to_file() {
    std::ofstream f(file_name);
    f.clear();
    for(const auto& q:arr){
        f<<q<<"\n";
    }
    f.close();
}

Repository::Repository() {
    read_from_file();
}

Repository::~Repository() {
    save_to_file();
}

int Repository::size() {
    return arr.size();
}

void Repository::add(const Question &q) {
    arr.push_back(q);
}

Question &Repository::operator[](int index) {
    if(index<0 || index>=this->size())
        throw "Bad index!";
    return arr[index];
}

int Repository::get_index_for_id(int id) {
    for(int i=0;i<this->size();i++)
        if(this->arr[i].getId()==id)
            return i;
    return -1;
}

std::vector<Question> Repository::get_all_questions() {
    return arr;
}
