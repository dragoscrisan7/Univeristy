#include "Repo.h"

#include <sstream>
#include <algorithm>

Repo::Repo() = default;

void Repo::read_from_file() {
    this->items.clear();
    ifstream f(R"(C:\Users\Dragos\OneDrive\Facultate\Year1Sem2\Object_Oriented_Programming\Examples\qt_project_2\Shopping_list)");
    if(!f.is_open())
        return;
    string text;
    while(getline(f,text)){
        stringstream s(text);
        int q;
        string c, n;
        s >> c;
        s >> n;
        s >> q;
        Item i{c, n, q};
        this->items.push_back(i);
    }
}

bool compare(Item i1, Item i2){
    int cmp = i1.get_category().compare(i2.get_category());
    if(cmp == 0){
        int cmp2 = i1.get_name().compare(i2.get_name());
        if(cmp2 > 0)
            return false;
        else
            return true;
    }
    else if(cmp > 0)
        return false;
    else
        return true;
}

void Repo::Sort() {
    sort(this->items.begin(), this->items.end(), compare);
}


