#pragma once

typedef struct
{
	char* name;
	char* type;
	double distanceToEarth;
} Planet;

/*
* Creates a new Planet and returns a pointer to it.
* Input: - name - array of characters
*		 - type - array of characters
*		 - dist - double 
* Output: p - pointer to the created planet		
*/
Planet* createPlanet(char* name, char* type, double dist);

/*
* Deallocates the memory occupied by the given planet.
* Input: p - pointer to planet
* Output: - deallocation
*/
void destroyPlanet(Planet* p);

char* getName(Planet* p);

void testPlanet();