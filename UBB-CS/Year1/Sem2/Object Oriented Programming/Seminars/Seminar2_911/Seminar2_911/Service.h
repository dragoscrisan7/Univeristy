#pragma once
#include "Repository.h"

class Service
{
private:
	Repository& repo;

public:
	Service(Repository& repository);

	void addSong(const std::string& title, const std::string& artist, int duration);
	int getSize() const;
};

