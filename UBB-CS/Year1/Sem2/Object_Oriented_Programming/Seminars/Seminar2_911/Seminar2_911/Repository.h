#pragma once
#include "DynamicVector.h"

class Repository
{
private:
	DynamicVector songs;

public:
	void addSong(const Song& s);
	int getSize() const;
};

