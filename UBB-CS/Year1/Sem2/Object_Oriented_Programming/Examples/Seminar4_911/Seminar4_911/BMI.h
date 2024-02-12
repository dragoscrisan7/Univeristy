#pragma once
#include "MedicalAanalysis.h"

class BMI :public MedicalAanalysis
{
private:
	double value;

public:
	BMI();
	BMI(const std::string& date, double value);
	bool isResultOK() override;
	std::string toString() const override;
	std::istream& read(std::istream& is) override;
};

