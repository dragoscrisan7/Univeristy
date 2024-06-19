#include "Service.h"

Service::Service(Repository& repository): repo{repository}
{}

void Service::addSong(const std::string & title, const std::string & artist, int duration)
{
	Song s{ title, artist, duration };
	this->repo.addSong(s);
}

int Service::getSize() const
{
	return this->repo.getSize();
}
