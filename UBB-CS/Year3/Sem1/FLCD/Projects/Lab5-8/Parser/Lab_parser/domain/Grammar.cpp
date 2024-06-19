#include "Grammar.h"
#include <algorithm>
#include <cctype>
#include <unordered_set>

Grammar::Grammar() : start_symbol("-"), nonterminals{}, terminals{} {}

void Grammar::read_grammar_from_file() {
    std::ifstream file(filename);
    if (file.is_open()) {
        try {
            // initializez semafoare
            std::string line;
            bool inside_nonterminals = false;
            bool inside_terminals = false;
            bool outside_terminals = false;
            int count = 0;

            bool inside_productions = false;

            /// citesc linie cu linie
            while (std::getline(file, line)) {
                bool before_arrow = true;
                if (line[0] == 'G') { /// daca o linie incepe cu G se considera definitia gramaticii
                    int ok = 0;
                    for (char c: line) {
                        if (c == '{' && ok == 0) {
                            inside_nonterminals = true;
                            ok = 1;
                        } else if (c == '}' && inside_nonterminals) {
                            inside_nonterminals = false;
                            inside_terminals = true;
                        } else if (c == '}' && inside_terminals) {
                            inside_terminals = false;
                            count = 1;
                            outside_terminals = true;
                        } else if (inside_nonterminals && isalpha(c)) {
                            nonterminals.push_back(std::string(1, c));
                        } else if (inside_terminals && isalpha(c)) {
                            terminals.push_back(std::string(1,c));
                        } else if (outside_terminals && isalpha(c)) {
                            if (count == 1) {
                                production_symbol = std::string(1, c);;
                                count++;
                            } else
                                start_symbol = std::string(1, c);
                        }
                    }
                }
                if (line[0] == production_symbol[0]) { /// daca da de production symbol din definitia gramaticii, atunci intra in stadiul de tokenizare si salvarea productiilor
                    inside_productions = true;
                } else if (inside_productions) {
//                    std::cout<<"Line: "<< line <<std::endl;
                    char *p = std::strtok(const_cast<char *>(line.data()), " ");
                    std::string current_production_token;
                    while (p) {
                        /// inainte de -> va lua ultimul non-terminal ca fiind terminalul asociat productiei
                        if (before_arrow) {
                            if (strcmp(p, "->")!=0) {
                                current_production_token = p;
//                                std::cout<<"Current production token:"<<current_production_token<<std::endl;
                            } else {
                                before_arrow = false;
                            }
                        } else {
                            /// daca da de elemente dupa sageata, le va asocia acelui non-terminal
                            if (p != "->" && p != "|") {
                                this->productions[current_production_token].push_back(p);
                            }
                        }
                        p = std::strtok(NULL, " |");
                    }
                }
            }
        } catch (const std::exception &e) {
            std::cerr << "Error reading grammar file: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}

void Grammar::read_grammar_from_file2() {
    std::ifstream file(filename);
    if (file.is_open()) {
        try {
            std::string line;
            bool inside_nonterminals = false;
            bool inside_terminals = false;
            bool outside_terminals = false;
            int count = 0;

            bool inside_productions = false;

            while (std::getline(file, line)) {
                std::string nonTerminal = line.substr(0, line.find(" ::="));
                nonterminals.push_back(nonTerminal);
            }

        }
        catch (const std::exception &e) {
            std::cerr << "Error reading grammar file: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}

void Grammar::print_nonterminals() {
    try {
        std::cout << "Non-terminals: ";
        for (auto v : this->nonterminals) {
            std::cout << v << " ";
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
        std::set<std::string> visited;

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
            if (std::find(nonterminals.begin(), nonterminals.end(), non_terminal) == nonterminals.end()){
                std::cerr << "Non_terminal Error: input should be a valid non_terminal " << non_terminal
                          << std::endl;
                return false;
            }
            for (const auto &prod_opt : production_options) {
                bool hasTerminal = false;
                bool hasNonterminal = false;

                for (char symbol : prod_opt) {
                    if (isupper(symbol) && std::find(nonterminals.begin(), nonterminals.end(), std::string(1, symbol)) == nonterminals.end()) {
                        std::cerr << "Production Option Error: invalid non_terminal " << symbol << std::endl;
                        return false;
                    } else if (islower(symbol) && std::find(terminals.begin(), terminals.end(), std::string(1, symbol)) == terminals.end()) {
                        std::cerr << "Production Option Error: invalid terminal " << symbol << std::endl;
                        return false;
                    }

                    if (islower(symbol)) {
                        hasTerminal = true;
                    } else if (isupper(symbol)) {
                        hasNonterminal = true;
                    }
                }

                for (const std::string &nonterm : nonterminals) {
                    if (std::none_of(productions.begin(), productions.end(),
                                     [nonterm](const auto &prod_pair) {
                                         return prod_pair.first == nonterm; // Compare with the left-hand side of each production rule
                                     })) {
                        std::cerr << "Production Rule Completeness Error: missing production rule for non_terminal "
                                  << nonterm << std::endl;
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

std::vector<std::string> Grammar::getNonTerminals() const {
    return this->nonterminals;
}

std::vector<std::string> Grammar::getTerminals() const {
    return this->terminals;
}

std::map<std::string, std::vector<std::string>> Grammar::getProductions() const {
    return this->productions;
}

std::string Grammar::getStartingSymbol() const {
    return this->start_symbol;
}
