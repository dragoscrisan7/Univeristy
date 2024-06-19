#include "Scanner.h"
#include <filesystem>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <regex>

namespace fs = std::filesystem;

Scanner::Scanner() {
    this->x = 0;
    this->pif_table = {};
    this->st = SymbolTable();
    this->tokens = ""; // "+ - * / = < <= == >= : != & |";
    this->separators = " \t";

    // "int float char string list if then else while read write declaration start end do";

    //TODO make these functions and call it here

    std::ifstream f("..\\elements\\token.in");
    if (f.is_open()) {
        std::string line;
        std::string data = " ";
        while (std::getline(f, line)) {
            data += line + " ";
        }
        this->tokens = data;
    }
    
    std::string path("..\\in_files\\");
    struct stat sb;
    for (const auto &entry: fs::directory_iterator(path)) {
        std::filesystem::path outfilename = entry.path();
        std::string outfilename_str = outfilename.string();
        const char *path = outfilename_str.c_str();
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
            this->files.push_back(path);
        }
    }
}

//TODO apply single responsibility principle :P

void Scanner::tokenize() {
    for (const auto &file: this->files) {
        this->x = 0;
        this->pif_table = {};
        this->st = SymbolTable();
        std::ifstream f(file); // declaration of filestreaming

        if (f.is_open()) {
            std::string line;
            bool signal = 1;

            while (std::getline(f, line) && signal == 1) {
                this->x++;

                char *pointer = std::strtok(line.data(), this->separators.c_str());

                while (pointer && signal == 1) {
                    int value = what_is_this_token(pointer);
//                    std::cout << "\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n";
//                    std::cout << "\n" << file << " with " << pointer << ":" << value << "\n\n";
                    if (value == 0) {
                        std::cerr << "\n Element: " << pointer << '\n';
                        std::cerr << "------------------------- ERROR --------------------\n";
                        std::cerr << "In " << file << " on line " << x << ": LEXICAL ERROR\n\n";
                        signal = 0;
                    } else if (value == -1) {
                        std::tuple<std::string, std::tuple<int, int>> t = std::make_tuple(pointer,
                                                                                          std::make_tuple(-1, -1));
                        this->pif_table.push_back(t);
                    } else {
                        this->st.insert(pointer);
                        int line = this->st.hash_function(pointer), column = this->st.lookup(pointer);
                        if (line == -1 || column == -1)
                            std::cout << "Something went wrong in the symbol table\n";
                        else {
                            std::string what_is_it = "";

                            if (value == 1)
                                what_is_it = "integer";
                            if (value == 3)
                                what_is_it = "character";
                            if (value == 4)
                                what_is_it = "float";
                            if (value == 6)
                                what_is_it = "string";
                            if (value == 7)
                                what_is_it = "variable";

                            std::tuple<std::string, std::tuple<int, int>> t = std::make_tuple(what_is_it,
                                                                                              std::make_tuple(line,
                                                                                                              column));
                            this->pif_table.push_back(t);
                        }
                    }
                    pointer = std::strtok(NULL, this->separators.c_str());
                }
            }
            if (signal == 1) {
                std::cout << "--------------- MESSAGE -----------------\n";
                std::cout << "File " << file << " is lexically correct.\n\n";
            }
            f.close();
        }
        save_to_pif(file);
        save_to_st(file);
    }
}

void Scanner::scan() {

}

int is_not_reserved_word(std::string reserved_words, std::string element) {
    std::string el = " " + element + " ";
    if (std::strstr(reserved_words.data(), el.c_str())) {
        //std::cout << std::strstr(reserved_words.data(), element.c_str()) << "\n";
        return 0;
    }
    return 1;
}

int Scanner::what_is_this_token(std::string element) {
    // Constants
    std::regex integer_pattern("^[+-]?[0-9]+$"); // numbers from -... to +..., integers only
    std::regex float_pattern("^[0-9]+\\.[0-9]*$"); /// numbers under the form: number . number

    std::regex character_pattern("^\'.\'$"); /// one character between single quotes
    std::regex string_pattern("^\".*\"$"); /// multiple characters between double quotes

    // Identifiers
    std::regex variable_pattern("^[A-Za-z]+$"); /// multiple characters only, and only letters (can be upper and lower)


    if (is_not_reserved_word(this->tokens, element) == 0){
        return -1;
    }
    else{
        if (std::regex_search(element, integer_pattern)) return 1;
        if (std::regex_search(element, float_pattern)) return 4;
        if (std::regex_search(element, character_pattern)) return 3;
        if (std::regex_search(element, string_pattern)) return 6;
        if (std::regex_search(element, variable_pattern)) return 7;
    }
    return 0;
}

std::string generate_name(std::string other_name,std::string file, std::string type) {
    std::string final_name = std::strcat(other_name.data(), type.c_str());
    std::string to_return = std::strcat(final_name.data(), file.c_str() + 12);
    return to_return;
}

void Scanner::save_to_pif(std::string file) {
    std::string name = generate_name( "..\\out_files\\", file, "pif_");
    std::ofstream f(name);
    if (f.is_open()) {
        for (const auto &entry: this->pif_table) {
            f << std::get<0>(entry) << " | " << std::get<0>(std::get<1>(entry)) << " "
                 << std::get<1>(std::get<1>(entry)) << "\n";
        }
        f.close();
        std::cout << "--------------------- MESSAGE -------------------\n";
        std::cout << "PIF for file: " << file << " has been written. \n\n";
    } else {
        std::cerr << "---------------------- ERROR --------------------\n";
        std::cerr << "Unable to open file " << file << " \n\n"; // ""console error CErr
    }
}

void Scanner::save_to_st(std::string file) {
    std::string name = generate_name( "..\\out_files\\", file, "st_");
    std::ofstream f(name);
    if (f.is_open()) {
        f << st.toString();
        f.close();
        std::cout << "--------------------- MESSAGE -------------------\n";
        std::cout << "SymbolTable for file: " << file << " has been written.\n\n";
    } else {
        std::cerr << "---------------------- ERROR --------------------\n";
        std::cerr << "Unable to open file " << file << " \n\n";

    }
}
