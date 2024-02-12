#include "Planet.h"
#include <string.h>
#include <stdlib.h>

Planet* createPlanet(char* name, char* type, double dist)
{
	Planet* p = malloc(sizeof(Planet));
	if (p == NULL)
	{
		return NULL;
	}
	p->name = malloc(sizeof(char) * (strlen(name) + 1));
	p->type = malloc(sizeof(char) * (strlen(type) + 1));
	if (p->name == NULL || p->type == NULL)
	{
		return NULL;
	}
	strcpy(p->name, name);
	strcpy(p->type, type);
	p->distanceToEarth = dist;
	return p;
}

void destroyPlanet(Planet* p)
{
	if (p == NULL)
	{
		return;
	}
	free(p->name);
	free(p->type);
	free(p);
}

char* getName(Planet* p)
{
	if (p == NULL)
		return NULL;
	return p->name;
}

void testPlanet()
{
	Planet* p = createPlanet("K10", "terrestrial", 100.5);
	destroyPlanet(p);
}