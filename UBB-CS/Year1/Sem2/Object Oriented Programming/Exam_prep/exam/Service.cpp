#include "Service.h"
#include <algorithm>
#include <fstream>


void Service::addIdea(std::string description, std::string creator, int act) {
    Idea idea{description, "proposed", creator, act};
    repo.addIdea(idea);
    this->sortAllIdeas();
}

void Service::acceptIdea(std::string description, int act) {
    int index = this->repo.searchForIdea(description, act);
    if(index==-1)
        throw "Failed\nIdea doesn't exist.";
    if(this->repo[index].getStatus()=="accepted")
        throw "Failed\nAlready accepted.";
    this->repo[index].setStatus("accepted");

}

Service::Service(IdeaRepo &repo) : repo(repo) {this->sortAllIdeas();}

std::vector<Idea> Service::allAcceptedIdeas() {
    std::vector<Idea> all = this->repo.allIdeas();
    std::vector<Idea> allAccepted;
    for(auto idea: all)
        if(idea.getStatus() == "accepted")
            allAccepted.push_back(idea);
    return allAccepted;
}

std::vector<Idea> Service::acceptedIdeasSortedByActs() {
    std::vector<Idea> accepted = this->allAcceptedIdeas();
    std::sort(accepted.begin(), accepted.end(), [](Idea i1, Idea i2){return i1.getAct()<i2.getAct();});
    return accepted;
}

void Service::saveToFileAcceptedIdeas() {
    std::ofstream f("C:\\Users\\Dragos\\CLionProjects\\exam\\Accepted.txt");
    std::vector accepted = this->acceptedIdeasSortedByActs();
    int i=0;
    for (int act=1;act<=3;act++)
    {
        f<<"Act "<<act<<":\n";
        while(i<accepted.size() && accepted[i].getAct()==act)
        {
            f<<accepted[i]<<"\n";
            i++;
        }
    }
    f.close();
}

std::vector<Idea> Service::allIdeas() {
    return this->repo.allIdeas();
}

void Service::sortAllIdeas() {
    std::vector<Idea> allIdeas = this->allIdeas();
    std::sort(allIdeas.begin(), allIdeas.end(), [](Idea idea1, Idea idea2){return idea1.getAct()<idea2.getAct();});
    this->repo.setRepo(allIdeas);
}
