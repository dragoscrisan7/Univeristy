#pragma once
#include "Song.h"

typedef Song TElem;

class DynamicVector
{
private:
	TElem* elems;
	int capacity, size;

	void resize();

public:
	DynamicVector(int capacity = 1);
	DynamicVector(const DynamicVector&);

	DynamicVector& operator=(const DynamicVector&);

	void add(TElem s);

	int getSize()const;

	~DynamicVector();
};



