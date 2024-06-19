#include "Repository.h"

Repository::Repository() {
    read_from_file_prog();
    read_from_file_source_files();
}

void Repository::read_from_file_prog() {
    std::ifstream f(filename1);
    while(!f.eof()){
        Programmer p;
        f>> p;
        this->programmers.push_back(p);
    }
    f.close();
}

void Repository::read_from_file_source_files() {
    std::ifstream f(filename2);
    while(!f.eof()){
        SourceFile q;
        f>> q;
        this->files.push_back(q);
    }
    f.close();
}

void Repository::save_to_file_prog() {
    std::ofstream f(filename1);
    f.clear();
    for(const auto& q:programmers){
        f<<q<<"\n";
    }
    f.close();
}

void Repository::save_to_file_source_file() {
    std::ofstream f(filename2);
    f.clear();
    for(const auto& q:files){
        f<<q<<"\n";
    }
    f.close();
}

const vector<Programmer> &Repository::getProgrammers() const {
    return programmers;
}

const vector<SourceFile> &Repository::getFiles() const {
    return files;
}

vector<SourceFile> Repository::sortedFiles() const {
    auto sorted_files = this->files;

    std::sort(sorted_files.begin(), sorted_files.end(), [](const SourceFile& s1, const SourceFile &s2){return s1.getName() == s2.getName();});

    return sorted_files;
}
