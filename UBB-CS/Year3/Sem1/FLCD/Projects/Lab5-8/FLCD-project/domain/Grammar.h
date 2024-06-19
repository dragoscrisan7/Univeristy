//
// Created by Dragos on 1/12/2024.
//

#ifndef FLCD_PROJECT_GRAMMAR_H
#define FLCD_PROJECT_GRAMMAR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>

#pragma once

class Grammar {
private:
    std::vector<std::pair<std::string, int>> nonterminals;
    std::vector<char> terminals;
    std::map<std::string, std::vector<std::string>> productions;
    char start_symbol;
    char production_symbol;
    std::string pif_filename = R"(..\out_files\pif_p1.txt)";
    std::string st_filename = R"(..\out_files\st_p1.txt)";

public:
    Grammar();
    void read_grammar_from_file();
    void print_nonterminals();
    void print_terminals();
    void print_productions();
    char get_starting(){return this->start_symbol;};
    char get_prod(){return this->production_symbol;};
    void productions_for_nonterminal(std::string nonterminal);
    bool is_cfg();

    void setFileName(std::string file){this->pif_filename = file;}
    std::map<std::string, std::vector<std::string>> getProductions() const;
    char getStartingSymbol() const;

    bool containsInfiniteLoop(const std::string &productionOption, std::set<char> &visited);
};

#endif //FLCD_PROJECT_GRAMMAR_H
