//
// Created by Oana on 5/23/2022.
//

#include <vector>
#include <sstream>
#include "Task.h"

Task::Task() {
    description = "";
    priority=0;
    duration=0;

}

Task::Task(std::string desc, int dur, int pri) {
    description=desc;
    duration=dur;
    priority=pri;
}

int Task::get_priority() const {
    return priority;
}

bool Task::operator<(const Task &t) {
    if (this->priority<t.priority || (this->priority==t.priority && this->duration<t.duration))
        return true;
    return false;
}

/*
	Tokenizes a string.
	Input:	str - the string to be tokenized.
			delimiter - char - the delimiter used for tokenization
	Output: a vector of strings, containing the tokens
*/
std::vector<std::string> tokenize(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Task &t) {
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 3)
        return is;
    t.description = tokens[0];
    t.duration = std::stoi(tokens[1]);
    t.priority = std::stoi(tokens[2]);
    return is;
}

int Task::get_duration() const {
    return duration;
}

std::string Task::to_string() const {
    std::string str = "Description: " + description + ", duration: " + std::to_string(duration) + ", priority: "+std::to_string(priority) + "\n";
    return str;
}
