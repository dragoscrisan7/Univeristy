#include "Animal.h"
#include <iostream>

using namespace std;

Animal::Animal(int a): age{a}
{
}

void Animal::speak()
{
	cout << "Generic animal ";
}
