#include "MedicalAanalysis.h"

MedicalAanalysis::MedicalAanalysis(): date{""}
{
}

MedicalAanalysis::MedicalAanalysis(const std::string& date): date{date}
{
}

std::string MedicalAanalysis::toString() const
{
    return this->date;
}

std::istream& operator>>(std::istream& is, MedicalAanalysis& a)
{
    return a.read(is);
}

std::ostream& operator<<(std::ostream& os, const MedicalAanalysis& a)
{
    os << a.toString();
    return os;
}
