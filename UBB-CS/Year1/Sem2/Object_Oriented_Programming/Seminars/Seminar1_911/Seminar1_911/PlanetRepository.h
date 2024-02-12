#pragma once
#include "Planet.h"

typedef struct
{
	Planet arr[100];
	int size;
} PlanetRepository;

void add(PlanetRepository* repo, Planet p);