#include "Repo.h"
#include <sstream>
#include <fstream>
#include <algorithm>


Repo::Repo() = default;

void Repo::loadData() {
    ifstream f(R"(C:\Users\Dragos\OneDrive\Facultate\Year1Sem2\Object_Oriented_Programming\Examples\untitled1\Weather)");
    if(!f.is_open())
        return;
    string text;
    while(getline(f, text)){
        stringstream s(text);
        string d;
        int start, e, t, p;
        s >> start;
        s >> e;
        s >> t;
        s >> p;
        s >> d;
        Weather w{start, e, t, p ,d};
        this->weathers.push_back(w);
    }
}

bool compare(Weather w1, Weather w2) {
    if (w1.get_start() > w2.get_start()) {
        return false;
    }
    return true;
}

void Repo::sortVector() {
    sort(this->weathers.begin(), this->weathers.end(), compare);
}
