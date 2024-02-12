//
// Created by Oana on 6/7/2022.
//
#pragma once
#include <vector>
#include "Idea.h"


class IdeaRepo {
private:
    std::vector<Idea> arr;
    std::string file_name="C:\\Users\\Dragos\\OneDrive\\Facultate\\Year1Sem2\\Object_Oriented_Programming\\Exam_prep\\practice_for_exam_2\\ideas.txt";
public:
    IdeaRepo();
    ~IdeaRepo();

    void readFromFile();
    void saveToFile();

    int searchForIdea(std::string description, int act);

    void addIdea(const Idea& idea);

    std::vector<Idea> allIdeas();

    Idea& operator[](int index);

    void setRepo(std::vector<Idea> ideas);
};

