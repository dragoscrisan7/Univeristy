#pragma once
#include "Programmer.h"
#include "SourceFile.h"
#include <fstream>
#include <algorithm>
#include "Observer.h"

class Repository: public Subject{
private:
    vector<Programmer> programmers;
    vector<SourceFile> files;
    string filename1 = "C:\\Users\\Dragos\\OneDrive\\Facultate\\Year1Sem2\\Object_Oriented_Programming\\Examples\\last_hope\\Programmers.txt";
    string filename2 = "C:\\Users\\Dragos\\OneDrive\\Facultate\\Year1Sem2\\Object_Oriented_Programming\\Examples\\last_hope\\SourceFiles.txt";
public:
    Repository();
    ~Repository(){save_to_file_prog(); save_to_file_source_file();}

    void read_from_file_prog();
    void read_from_file_source_files();
    void save_to_file_prog();
    void save_to_file_source_file();

    const vector<Programmer> &getProgrammers() const;

    const vector<SourceFile> &getFiles() const;

    vector<SourceFile> sortedFiles() const;

    void add_file(SourceFile& sf){this->files.push_back(sf); notify();}
};

