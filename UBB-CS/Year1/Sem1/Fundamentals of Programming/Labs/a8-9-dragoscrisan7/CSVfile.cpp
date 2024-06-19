#include "CSVfile.h"
#include <fstream>

csvfile::csvfile(std::vector<dog> &adopted, std::string &filename) {
    this->adopted = adopted;
    this->userfilename = filename;
}

int csvfile::getSize() {
    return this->adopted.size();
}

std::string &csvfile::getFileName() {
    return this->userfilename;
}

std::vector<dog> csvfile::getDog() {
    return this->adopted;
}

void csvfile::writeToFile() {
    std::ofstream fout(this->userfilename);
    if(!this->adopted.empty()){
        for(const dog& dog1: this->adopted){
            fout<<dog1.get_breed()<<","<<dog1.get_name()<<","<<dog1.get_photograph()<<","<<dog1.get_age()<<"\n";
        }
    }
    fout.close();
}

void csvfile::open() {
    auto * fp = R"(C:\Users\Dragos\OneDrive\Facultate\GitHub\a8-9-dragoscrisan7\AdoptedList.csv)";
    ShellExecute(NULL, NULL,fp, NULL, NULL, SW_SHOWNORMAL);
}

