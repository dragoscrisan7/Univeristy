#include "IdeaRepo.h"
#include <fstream>

IdeaRepo::IdeaRepo() {
    readFromFile();
}

IdeaRepo::~IdeaRepo() {
    //saveToFile();

}

void IdeaRepo::readFromFile() {
    std::ifstream f(file_name);
    Idea input{};
    while(f>>input){
        arr.push_back(input);
    }
    f.close();

}

void IdeaRepo::saveToFile() {
    std::ofstream f(file_name);
    for (auto idea: arr)
        f<<idea<<"\n";
    f.close();
}

void IdeaRepo::addIdea(const Idea &idea) {
    if (idea.getAct()<1 || idea.getAct()>3)
        throw "Failed\nNot a valid act.";
    if(idea.getDescription()=="")
        throw "Failed\nEmpty description.";
    if(this->searchForIdea(idea.getDescription(), idea.getAct())!=-1)
        throw "Failed\nDescription already exists.";
    arr.push_back(idea);
}

int IdeaRepo::searchForIdea(std::string description, int act) {
    for(int i=0;i<arr.size();i++)
        if (description == arr[i].getDescription() && act == arr[i].getAct())
            return i;
    return -1;
}

Idea &IdeaRepo::operator[](int index) {
    return arr[index];
}

std::vector<Idea> IdeaRepo::allIdeas() {
    return arr;
}

void IdeaRepo::setRepo(std::vector<Idea> ideas) {
    arr=ideas;
}
