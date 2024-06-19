//
// Created by Dragos on 6/27/2022.
//

#include "QRepo.h"

QRepo::QRepo(){
    read_from_file();
}

QRepo::~QRepo() {
    save_to_file();
}

vector<Questions> QRepo::getALL() {
    return arr;
}

void QRepo::add_question(Questions &q) {
    arr.push_back(q);
}

int QRepo::answer_question(int id, string &answer) {
    for(auto q: arr){
        if(q.getId() == id){
            if(q.getCorrectAnswer() == answer)
                return q.getScore();
            else
                return 0;
        }
    }
    return 0;
}

int QRepo::find_by_id(int id) {
    for(int i=0; i<arr.size(); i++){
        if(arr[i].getId() == id)
            return i;
    }
    return -1;
}

Questions &QRepo::operator[](int index) {
    if(index<0 || index>=arr.size())
        throw "bad index";
    else
        return arr[index];
}

void QRepo::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Questions q;
        f>> q;
        if(q.getText().empty())
            break;
        this->arr.push_back(q);
    }
    f.close();

}

void QRepo::save_to_file() {
    std::ofstream f(file_name);
    f.clear();
    for(const auto& q:arr){
        f<<q<<"\n";
    }
    f.close();
}


