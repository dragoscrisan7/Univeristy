#include "PlanetRepository.h"

void add(PlanetRepository* repo, Planet p)
{
	// add
	repo->arr[repo->size++] = p;
	operation o = createOperation("add", p);
}
