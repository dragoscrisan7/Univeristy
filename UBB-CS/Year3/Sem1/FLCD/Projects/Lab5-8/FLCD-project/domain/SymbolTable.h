#pragma once

#include <string>
#include <vector>

class SymbolTable {
private:
    int length;
    std::vector<std::vector<std::string>> list; // position -> nr(index), content -> list of variables

public:
    SymbolTable() : length(100), list(std::vector<std::vector<std::string>>(100)) {}
    SymbolTable(int len) : length(len), list(std::vector<std::vector<std::string>>(len)) {}
    ~SymbolTable() {}

    int insert(const std::string& name);
    int lookup(const std::string& name);
    int hash_function(const std::string& name);

    std::string toString();
};
