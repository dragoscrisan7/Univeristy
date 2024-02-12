//
// Created by Dragos on 7/5/2022.
//

#include "Task.h"

Task::Task(const string &description, const string &status, int id) : description(description), status(status),
                                                                      id(id) {}

Task::~Task() {

}

Task::Task() {
    description = "";
    status = "open";
    id = 0;
}

const string &Task::getDescription() const {
    return description;
}

void Task::setDescription(const string &description) {
    Task::description = description;
}

const string &Task::getStatus() const {
    return status;
}

void Task::setStatus(const string &status) {
    Task::status = status;
}

int Task::getId() const {
    return id;
}

void Task::setId(int id) {
    Task::id = id;
}

ostream &operator<<(ostream &os, const Task &task) {
    os << task.description << "," << task.status << "," << task.id;
    return os;
}

vector<string> separate_words(string line, char delimiter)
{
    vector<string> words;
    stringstream l(line);
    string token;
    while (getline(l, token, delimiter))
        words.push_back(token);

    return words;
}

istream &operator>>(istream &is, Task &task){
    string line;
    getline(is, line);

    vector<string> tokens = separate_words(line, ',');
    if (tokens.size() != 3)
        return is;
    task.setId(stoi(tokens[2]));
    task.setDescription(tokens[0]);
    task.setStatus(tokens[1]);
    return is;
}
