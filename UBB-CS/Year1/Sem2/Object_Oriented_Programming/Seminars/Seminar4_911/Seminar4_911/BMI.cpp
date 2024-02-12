#include "BMI.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "Utils.h"

BMI::BMI() : MedicalAanalysis{}, value{ 0 }
{
}

BMI::BMI(const std::string& date, double value): MedicalAanalysis{date}
{
    this->value = value;
}

bool BMI::isResultOK()
{
    if (this->value >= 18.5 && this->value <= 25) {
        return true;
    }
    return false;
}

std::string BMI::toString() const
{
    std::stringstream s;
    s << this->date << "," << this->value;
    return s.str();
}

std::istream& BMI::read(std::istream& is)
{
    std::string line;
    getline(is, line);
    std::vector<std::string> tokens = tokenize(line, ',');

    if (tokens.size() != 2)
        return is;
    this->date = tokens[0];
    this->value = stod(tokens[1]);

    return is;
}
