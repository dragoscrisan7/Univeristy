#pragma once
#include <string>
#include <iostream>

class MedicalAanalysis
{
protected:
	std::string date;

public:
	MedicalAanalysis();
	MedicalAanalysis(const std::string& date);

	virtual bool isResultOK() = 0;

	virtual std::string toString() const;

	virtual std::istream& read(std::istream& is) = 0;

	virtual ~MedicalAanalysis() {}

	friend std::istream& operator>>(std::istream& is, MedicalAanalysis& a);
	friend std::ostream& operator<<(std::ostream& os, const MedicalAanalysis& a);
};

