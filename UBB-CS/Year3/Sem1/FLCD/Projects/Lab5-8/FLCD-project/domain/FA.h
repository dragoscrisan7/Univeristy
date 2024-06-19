#pragma once
#include <vector>
#include <cstring>
#include <string>
#include <tuple>

class FA {
private:
    std::vector<std::string> states;
    std::vector<std::string> alphabet;
    std::vector<std::tuple<std::string, std::tuple<std::string, std::string>>> transitions;
    std::string initial_state;
    std::vector<std::string> final_states;
    std::string example;
    std::string file_name;
    bool determinisc_value;

public:
    FA();
    void read_file();
    void is_deterministic();
    void display();

};
