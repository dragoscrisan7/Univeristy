#include "HTMLfile.h"
#include <fstream>
int htmlfile::getSize() {
    return this->adopted.size();
}

std::string &htmlfile::getFileName() {
    return this->userfilename;
}

std::vector<dog> htmlfile::getDog() {
    return this->adopted;
}

void htmlfile::writeToFile() {
    std::ofstream fout(this->userfilename);
    fout << "<!DOCTYPE html>\n<html><head><title>Adoption List</title></head><body>\n";
    fout << "<table border=\"1\">\n";
    fout << "<tr><td>Breed</td><td>Name</td><td>Age</td><td>Link</td></tr>\n";
    for(const dog& dog1: this->adopted){
        fout << "<tr><td>" << dog1.get_breed() << "</td>"
             << "<td>" << dog1.get_name() << "</td>"
             << "<td>" << std::to_string(dog1.get_age()) << "</td>"
             << "<td><a href=\"" << dog1.get_photograph() << "\">"<<dog1.get_photograph()<<">Link</a></td></tr>" << '\n';
    }
    fout << "</table></body></html>";
    fout.close();
}

htmlfile::htmlfile(std::vector<dog> &adopted, std::string &filename) {
    this->adopted = adopted;
    this->userfilename = filename;
}

void htmlfile::open() {
    auto * fp = "C:\\Users\\Dragos\\OneDrive\\Facultate\\Year1Sem2\\Object_Oriented_Programming\\Examples\\untitled\\AdoptedList.html";
    ShellExecute(NULL, NULL, reinterpret_cast<LPCWSTR>(fp), NULL, NULL, SW_SHOWNORMAL);
}

