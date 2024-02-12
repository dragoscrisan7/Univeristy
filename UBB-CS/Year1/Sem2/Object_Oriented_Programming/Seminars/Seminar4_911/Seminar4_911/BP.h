#pragma once
#include "MedicalAanalysis.h"

class BP: public MedicalAanalysis
{
private:
	int systolicValue;
	int diastolicValue;
public:

	BP(const std::string& date, int systolicValue, int diastolcValue);
	bool isResultOK() override;
	std::string toString() const override;
	std::istream& read(std::istream& is) override;
};

