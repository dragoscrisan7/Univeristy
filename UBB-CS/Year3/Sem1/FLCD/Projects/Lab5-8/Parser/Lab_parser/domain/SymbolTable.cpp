#include "SymbolTable.h"

#include <sstream>
#include <iostream>

int SymbolTable::insert(const std::string& name) {
    if (lookup(name) != -1) {
        return 0;
    } else {
        int i = hash_function(name);
        this->list[i].push_back(name);
        return lookup(name);
    }
}

int SymbolTable::lookup(const std::string& name) {
    int i = hash_function(name);
    for (size_t j = 0; j < this->list[i].size(); ++j) {
        if (list[i][j] == name) {
            return j;
        }
    }
    return -1;
}

int SymbolTable::hash_function(const std::string& name) {
    int ascii_sum = 0;
    for (char ch : name) {
        ascii_sum += ch;
    }
//    std::cout<<name<<" with hash "<<ascii_sum <<"%" << this->length<<"\n";
    return (ascii_sum % this->length);
}

std::string SymbolTable::toString() {
    std::stringstream ss;
    for (int i = 0; i < this->length; i++) {
        if (!list[i].empty()) {
            ss << "Index " << i << ": {";
            for (const auto& variable : list[i])
                ss << variable << ", ";
            ss << "}\n";
        } else
            ss << "";
    }
    return ss.str();
}
