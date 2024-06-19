#include "Planet.h"
#include <crtdbg.h>
#include <stdio.h>
#include "PlanetRepository.h"

int main()
{
	//testPlanet();

	Planet* p = createPlanet("K10", "terrestrial", 100.5);
	char* name = getName(p);

	_CrtDumpMemoryLeaks();
}