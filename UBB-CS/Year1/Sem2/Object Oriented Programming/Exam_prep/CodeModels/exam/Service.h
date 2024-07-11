#pragma once
#include "IdeaRepo.h"

class Service {
private:
    IdeaRepo& repo;

public:
    Service(IdeaRepo &repo);

    void addIdea(std::string description, std::string creator, int act);

    void acceptIdea(std::string description, int act);

    std::vector<Idea> allAcceptedIdeas();

    std::vector<Idea> acceptedIdeasSortedByActs();

    void saveToFileAcceptedIdeas();

    std::vector<Idea> allIdeas();

    void sortAllIdeas();
};
