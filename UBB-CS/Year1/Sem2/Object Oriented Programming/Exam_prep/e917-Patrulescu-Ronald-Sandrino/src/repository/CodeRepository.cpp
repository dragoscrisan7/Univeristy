//
// Created by kamui on 08.06.2022.
//

#include "CodeRepository.h"
#include <fstream>
#include <algorithm>

CodeRepository::CodeRepository() {
    readProgrammers();
    readSourceFiles();
}

const vector<Programmer> &CodeRepository::getProgrammers() const {
    return programmers;
}

const vector<SourceFile> &CodeRepository::getSourceFiles() const {
    return sourceFiles;
}

void CodeRepository::readProgrammers() {
    string filename = "programmers.txt";
    ifstream f(filename);
    
    if (!f.is_open()) {
        fprintf(stderr, "Could not read from %s\n", filename.c_str());
        return;
    }
    
    Programmer p;
    while (f >> p) { programmers.push_back(p); }
}

void CodeRepository::readSourceFiles() {
    string filename = "sourceFiles.txt"; // NOTE: add a blank line at the end, due to the SourceFile operator>>
    ifstream f(filename);

    if (!f.is_open()) {
        fprintf(stderr, "Could not read from %s\n", filename.c_str());
        return;
    }

    SourceFile p;
    while (f >> p) { sourceFiles.push_back(p); }
}

void CodeRepository::addSourceFile(const string& name, Programmer &programmer) noexcept(false) {
    if (name.empty()) throw std::runtime_error("Source file name must not be empty");

    for (const auto &sourceFile: sourceFiles)
        if (sourceFile.getName() == name)
            throw std::runtime_error("Source file name must be unique");

    sourceFiles.emplace_back(name, "not_revised", programmer.getName(), "");
    notify();
}

vector<SourceFile> CodeRepository::getSortedSourceFiles() const {
    auto sortedSourceFiles = this->sourceFiles;

    // sort the source files by name
    std::sort(sortedSourceFiles.begin(), sortedSourceFiles.end(), [](const SourceFile& sf1, const SourceFile& sf2) {
        return sf1.getName() < sf2.getName();
    });

    return sortedSourceFiles;
}

SourceFile CodeRepository::findSortedSourceFileByIndex(int index) const noexcept(false) {
    if (not isIndexValid(index))
        throw std::runtime_error("Invalid source file selected");

    return getSortedSourceFiles()[index];
}

void CodeRepository::reviseSourceFile(const string& name, Programmer &programmer) noexcept(false) {
    // can throw, but, theoretically, it shouldn't since the original source of the name is the source files vector
    auto& sourceFile = findSourceFileByName(name);

    sourceFile.revise(programmer.getName());
    programmer.revise();

    notify();
}

SourceFile &CodeRepository::findSourceFileByName(const string& name) noexcept(false) {
    for (auto &sourceFile: sourceFiles)
        if (sourceFile.getName() == name)
            return sourceFile;

    throw std::runtime_error("Invalid source file selected"); // NOTE: the message is wrong. That source file just doesn't exist.
}
