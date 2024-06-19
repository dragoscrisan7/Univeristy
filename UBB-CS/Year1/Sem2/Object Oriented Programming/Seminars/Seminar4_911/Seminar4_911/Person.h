#pragma once
#include <string>
#include <vector>
#include "MedicalAanalysis.h"

class Person {
private:
	std::string name;
	std::vector<MedicalAanalysis*> analysis;

public:
	Person(const std::string& name);
	void addAllAnalyses(const std::string& BMIFileName, const std::string& BPFileName);
	std::vector<MedicalAanalysis*> getAllAnalyses();
	~Person();
};

