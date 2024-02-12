#pragma once
#include <iostream>

using namespace std;

class Weather{
private:
    int start, end, temperature, prec_prob;
    string description;
public:
    Weather();
    Weather(int s, int e, int t, int p, string d);

    int get_start(){return start;}
    int get_end(){return end;}
    int get_temp(){return temperature;}
    int get_prec(){return prec_prob;}
    string get_desc(){return description;}

    string To_string();
};