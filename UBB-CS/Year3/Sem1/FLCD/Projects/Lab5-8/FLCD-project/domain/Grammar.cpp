#include "Grammar.h"
#include <algorithm>
#include <cctype>
#include <sstream>

Grammar::Grammar() : start_symbol('-'), nonterminals{}, terminals{} {}

void Grammar::print_nonterminals() {
    try {
        std::cout << "Non-terminals: ";
        for (auto& v : this->nonterminals) {
            std::cout << v.first << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error in print_nonterminals: " << e.what() << std::endl;
    }
}

void Grammar::print_terminals() {
    try {
        std::cout << "Terminals: ";
        for (auto v : this->terminals) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error in print_terminals: " << e.what() << std::endl;
    }
}

void Grammar::print_productions() {
    try {
        for (auto entry : productions) {
            std::string non_terminal = entry.first;
            std::vector<std::string> &production_options = entry.second;

            std::cout << non_terminal << " -> ";

            for (size_t i = 0; i < production_options.size(); ++i) {
                std::cout << production_options[i];

                if (i < production_options.size() - 1) {
                    std::cout << " | ";
                }
            }

            std::cout << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error in print_productions: " << e.what() << std::endl;
    }
}

void Grammar::productions_for_nonterminal(std::string nonterminal) {
    try {
        auto it = productions.find(nonterminal);
        if (it != productions.end()) {
            std::vector<std::string> production_options = it->second;
            std::cout << nonterminal << " -> ";

            for (size_t i = 0; i < production_options.size(); ++i) {
                std::cout << production_options[i];

                if (i < production_options.size() - 1) {
                    std::cout << " | ";
                }
            }

            std::cout << std::endl;
        } else {
            throw std::out_of_range("Non-terminal not found");
        }
    } catch (const std::exception &e) {
        std::cerr << "Error in productions_for_nonterminal: " << e.what() << std::endl;
    }
}

bool contains(
        const std::vector<char> str,
        char targetChar) {
    return std::find(str.begin(), str.end(), targetChar) != str.end();
}

bool isLowerCase(char c) {
    return std::islower(static_cast<unsigned char>(c)) != 0;
}

bool Grammar::is_cfg() {
    try{
        std::set<char> visited;

        for(const auto &entry: productions){
            std::string non_terminal = entry.first;///check for non-terminals
            const auto &production_options = entry.second;///check for (non)terminals


            if(non_terminal.length() > 1) {
                std::cerr << "Non_terminal Error: input should be a single character " << non_terminal
                          << std::endl;
                return false;
            }
            if(!isalpha(non_terminal[0])){
                std::cerr << "Non_terminal Error: input should be a letter " << non_terminal
                          << std::endl;
                return false;
            }
            if(isLowerCase(non_terminal[0])){
                std::cerr << "Non_terminal Error: input should be an upper case letter " << non_terminal
                          << std::endl;
                return false;
            }
            if (std::find_if(nonterminals.begin(), nonterminals.end(), [&non_terminal](const auto &nt) {
                return nt.first[0] == non_terminal[0];
            }) == nonterminals.end()) {
                std::cerr << "Non_terminal Error: input should be a valid non_terminal " << non_terminal << std::endl;
                return false;
            }
            for (const auto &prod_opt : production_options) {
                bool hasTerminal = false;
                bool hasNonterminal = false;

                for (char symbol : prod_opt) {
                    if (isupper(symbol) && !std::any_of(nonterminals.begin(), nonterminals.end(),
                                                        [symbol](const auto &nt) {
                                                            return nt.first[0] == symbol;
                                                        })) {
                        std::cerr << "Production Option Error: invalid non_terminal " << symbol << std::endl;
                        return false;
                    } else if (islower(symbol) && !contains(terminals, symbol)) {
                        std::cerr << "Production Option Error: invalid terminal " << symbol << std::endl;
                        return false;
                    }

                    if (islower(symbol)) {
                        hasTerminal = true;
                    } else if (isupper(symbol)) {
                        hasNonterminal = true;
                    }
                }

                for (const auto &nt : nonterminals) {
                    if (std::none_of(productions.begin(), productions.end(),
                                     [&nt](const auto &prod_pair) {
                                         return prod_pair.first[0] == nt.first[0]; // Compare with the left-hand side of each production rule
                                     })) {
                        std::cerr << "Production Rule Completeness Error: missing production rule for non_terminal "
                                  << nt.first << std::endl;
                        return false;
                    }
                }
            }
            visited.clear();
        }
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error in is_cfg: " << e.what() << std::endl;
        return false;
    }
}

std::map<std::string, std::vector<std::string>> Grammar::getProductions() const {
    return this->productions;
}

char Grammar::getStartingSymbol() const {
    return this->start_symbol;
}

