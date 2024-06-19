#include "BP.h"
#include <sstream>

BP::BP(const std::string& date, int systolicValue, int diastolcValue): MedicalAanalysis{date}
{
    this->systolicValue = systolicValue;
    this->diastolicValue = diastolcValue;
}

bool BP::isResultOK()
{
    if (this->systolicValue >= 90 && this->systolicValue <= 119 && this->diastolicValue >= 60 && this->diastolicValue <= 79) {
        return true;
    }
    return false;
}

std::string BP::toString() const
{
    std::stringstream s;
    s << this->date << "," << this->systolicValue << "," << this->diastolicValue << "\n";
    return s.str();
}

std::istream& BP::read(std::istream& is)
{
    return is;
}
