#include "Repository.h"

void Repository::addSong(const Song& s)
{
	this->songs.add(s);
}

int Repository::getSize() const
{
	return this->songs.getSize();
}
