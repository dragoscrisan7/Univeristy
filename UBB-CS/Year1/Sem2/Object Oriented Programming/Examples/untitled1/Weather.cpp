#include "Weather.h"

Weather::Weather() {
    start = 0;
    end = 0;
    temperature = 0;
    prec_prob = 0;
    description = "";
}

Weather::Weather(int s, int e, int t, int p, string d) {
    start = s;
    end = e;
    temperature = t;
    prec_prob = p;
    description = d;
}

string Weather::To_string() {
    string str = "Start: " + to_string(start) + ", End: " + to_string(end) + ", Temperature: " + to_string(temperature) + ", Precpitation prob.: " +
            to_string(prec_prob) + ", Description: " + description + '\n';
    return str;
}
