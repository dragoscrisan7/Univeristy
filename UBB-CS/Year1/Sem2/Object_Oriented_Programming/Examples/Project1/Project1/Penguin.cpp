#include "Penguin.h"
#include <iostream>

using namespace std;

Penguin::Penguin(int age, const std::string& col): Animal{age}, colour{col}
{
}

void Penguin::speak()
{
	cout << "Gaw gaw gaw";
}
