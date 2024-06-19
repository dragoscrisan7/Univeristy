#pragma once
#include "Planet.h"

typedef struct
{
	char type[50];
	Planet planet;
} operation;

typedef struct
{
	operation arr[100];
	int size;
} UndoList;

operation createOperation(char* type, Planet p);

