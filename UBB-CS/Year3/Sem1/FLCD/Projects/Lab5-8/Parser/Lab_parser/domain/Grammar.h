#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>

#pragma once

class Grammar {
private:
    std::vector<std::string> nonterminals;
    std::vector<std::string> terminals;
    std::map<std::string, std::vector<std::string>> productions;
    std::string start_symbol;
    std::string production_symbol;
    std::string filename = "..\\grammar_files\\g1.txt";

public:
    Grammar();
    void read_grammar_from_file();
    void read_grammar_from_file2();
    void print_nonterminals();
    void print_terminals();
    void print_productions();
    std::string get_starting(){return this->start_symbol;};
    std::string get_prod(){return this->production_symbol;};
    void productions_for_nonterminal(std::string nonterminal);
    bool is_cfg();

    std::vector<std::string> getNonTerminals() const;
    std::vector<std::string> getTerminals() const;
    void setFileName(std::string file){this->filename = file;}
    std::map<std::string, std::vector<std::string>> getProductions() const;
    std::string getStartingSymbol() const;

    bool containsInfiniteLoop(const std::string &productionOption, std::set<char> &visited);
};