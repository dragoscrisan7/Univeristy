#pragma once
#include "../domain/SymbolTable.h"
#include <tuple>
#include <vector>

class Scanner {
private:
    SymbolTable st; // hashCode: variabile // linie + coloana
    std::vector<std::string> files;

    std::string separators = "";

    std::string tokens = ""; // reserved words and operators

    std::vector<std::tuple<std::string, std::tuple<int, int>>> pif_table; // element, linie, coloana

    int x; // x - line (error should be line + token / element where the error occurs)

public:
    Scanner();
    Scanner(std::vector<std::string> files): files(files){};

    void tokenize(); // elements will remember the file elements
    void scan();
    int what_is_this_token(std::string element); // returns number -> number associated with the role
    void save_to_pif(std::string file);
    void save_to_st(std::string file);
};
