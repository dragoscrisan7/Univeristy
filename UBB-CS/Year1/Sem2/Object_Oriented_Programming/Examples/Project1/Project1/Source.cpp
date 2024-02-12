#include "Penguin.h"

int main()
{
	Animal* p = new Penguin{ 2, "black" };
	p->speak();

	delete p;

	return 0;
}