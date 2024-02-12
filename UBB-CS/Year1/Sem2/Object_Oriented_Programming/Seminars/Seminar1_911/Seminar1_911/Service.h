#pragma once
#include "PlanetRepository.h"
#include "Undo.h"

typedef struct
{
	PlanetRepository* repo;
} Service;

Service* createService(PlanetRepository* repo);

void addPlanet(Service* s, Planet p);

void undo(UndoList undo);
