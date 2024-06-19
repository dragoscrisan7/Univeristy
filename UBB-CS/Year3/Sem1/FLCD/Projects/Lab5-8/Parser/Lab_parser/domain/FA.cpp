#include <fstream>
#include <iostream>
#include <algorithm>
#include "FA.h"

FA::FA() {
    this->alphabet = {};
    this->states = {};
    this->transitions = {};
    this->final_states = {};

    this->initial_state = "";
    this->file_name = "..\\elements\\FA.in";
    this->example = "";

    this->determinisc_value = true; // here we see if the example is deterministic (respects the FA rules)
}

void FA::read_file() {
    std::ifstream f(this->file_name);
    if (f.is_open()) {
        std::string line;
        int step = 0;
        int signal = 0;
        while (std::getline(f, line)) {
            char *pointer = std::strtok(line.data(), " ");
            std::string e1, e2, e3;
            int step_tuple = 0;
            while (pointer) {
                if (!std::strchr(pointer, ':')) {
                    if (step == 0)
                        this->states.push_back(pointer);
                    else if (step == 1)
                        this->alphabet.push_back(pointer);
                    else if (step == 2)
                        this->initial_state = pointer;
                    else if (step == 3)
                        this->final_states.push_back(pointer);
                    else if (step == 4)
                        this->example = pointer;
                    else {
                        if (step_tuple == 0) {
                            e1 = pointer;
                            step_tuple++;
                            signal = 0;
                        }
                        else if (step_tuple == 1) {
                            e2 = pointer;
                            step_tuple++;
                            signal = 0;
                        }
                        else if (step_tuple == 2) {
                            e3 = pointer;
                            step_tuple++;
                            signal = 1;
                        }
                    }
                }
                std::tuple<std::string, std::tuple<std::string, std::string>> t = std::make_tuple(e1,
                                                                                                  std::make_tuple(e2,
                                                                                                                  e3));
                if(step > 4 && signal == 1)
                    this->transitions.push_back(t);
                pointer = std::strtok(NULL, " ");
            }
            step++;
        }
    }
    f.close();
}

void FA::is_deterministic() {
    std::string current_state = this->initial_state;
    int index = 0;

    while (index < this->example.length()) {
        char current_input = this->example[index];
        bool found_transition = false;

        for (auto transition : this->transitions) {
            std::string source_state = std::get<0>(transition);
            std::tuple<std::string, std::string> transition_details = std::get<1>(transition);
            std::string transition_input = std::get<0>(transition_details);
            std::string destination_state = std::get<1>(transition_details);

            if (source_state == current_state && transition_input[0] == current_input) {
                current_state = destination_state;
                found_transition = true;
                break;
            }
        }

        if (!found_transition) {
            this->determinisc_value = false;
            return;
        }

        index++;
    }

    this->determinisc_value = true;
}

void FA::display() {
    std::cout << "------------------------- MENU --------------------\n";
    std::cout << "------------------------- STATES --------------------\n";
    for (auto &s: this->states)
        std::cout << "State: " << s << '\n';
    std::cout << "---------------------- ALPHABET ---------------------\n";
    for (auto &a: this->alphabet)
        std::cout << "Element: " << a << '\n';
    std::cout << "-------------------- TRANSITIONS --------------------\n";
    for (auto &t: this->transitions)
        std::cout << "Transition: " << std::get<0>(t) << "-" << std::get<0>(std::get<1>(t)) << "->"
                  << std::get<1>(std::get<1>(t)) << '\n';
    std::cout << "-------------------- INITIAL STATE -------------------\n";
    std::cout << "Initial state: " << this->initial_state << '\n';
    std::cout << "-------------------- FINAL STATES -------------------\n";
    for (auto &f: this->final_states)
        std::cout << "Final state: " << f << '\n';
    std::cout << "---------------- DETERMINISM TEST ----------------\n";
    std::cout << "The given example is:";
    if(this->determinisc_value)
        std::cout << " deterministic.\n";
    else
        std::cout << " non-deterministic.\n";
    std::cout << "---------------------------------------------------\n";
}
