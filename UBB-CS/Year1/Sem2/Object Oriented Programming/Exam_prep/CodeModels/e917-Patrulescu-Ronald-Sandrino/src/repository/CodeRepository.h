//
// Created by kamui on 08.06.2022.
//

#ifndef E917_PATRULESCU_RONALD_SANDRINO_CODEREPOSITORY_H
#define E917_PATRULESCU_RONALD_SANDRINO_CODEREPOSITORY_H
#include <iostream>
#include <vector>
#include "../domain/Programmer.h"
#include "../domain/SourceFile.h"
#include "../domain/observer.h"


using namespace std;

class CodeRepository: public Subject {
private:
    vector<Programmer> programmers;
    vector<SourceFile> sourceFiles;
public:
    CodeRepository();

    const vector<Programmer> &getProgrammers() const;
    const vector<SourceFile> &getSourceFiles() const;
    vector<SourceFile> getSortedSourceFiles() const;
    bool isIndexValid(int index) const { return index >= 0 and index < sourceFiles.size(); }
    SourceFile findSortedSourceFileByIndex(int index) const noexcept(false);
    void reviseSourceFile(const string& name, Programmer& programmer) noexcept(false);

    void addSourceFile(const string& name, Programmer& programmer) noexcept(false);

private:
    void readProgrammers();
    void readSourceFiles();

    SourceFile& findSourceFileByName(const string& name) noexcept(false);
};


#endif //E917_PATRULESCU_RONALD_SANDRINO_CODEREPOSITORY_H
