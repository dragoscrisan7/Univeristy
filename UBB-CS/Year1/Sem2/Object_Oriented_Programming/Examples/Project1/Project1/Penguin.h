#pragma once
#include "Animal.h"
#include <string>

class Penguin: public Animal
{
private:
	std::string colour;

public:
	Penguin(int age, const std::string& col);

	void speak() override;
};

