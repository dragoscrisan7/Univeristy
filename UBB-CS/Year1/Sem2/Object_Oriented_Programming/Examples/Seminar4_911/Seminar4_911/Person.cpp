#include "Person.h"
#include "BMI.h"
#include "BP.h"
#include <fstream>

using namespace std;

Person::Person(const std::string& name) : name(name) {}

void Person::addAllAnalyses(const std::string& BMIFileName, const std::string& BPFileName) {
    ifstream iBMI{ BMIFileName };
    
    BMI bmi{};
    while (iBMI >> bmi)
    {
        MedicalAanalysis* p_bmi = new BMI{bmi};
        this->analysis.push_back(p_bmi);
    }
    
    
    /*MedicalAanalysis* bmi = new BMI{ "2022.04.13", 22 };
    MedicalAanalysis* bp = new BP{ "2022.04.13", 65, 100 };

    this->analysis.push_back(bmi);
    this->analysis.push_back(bp);*/
}

std::vector<MedicalAanalysis*> Person::getAllAnalyses() {
    return this->analysis;
}

Person::~Person()
{
    // TO DO !!!
}
