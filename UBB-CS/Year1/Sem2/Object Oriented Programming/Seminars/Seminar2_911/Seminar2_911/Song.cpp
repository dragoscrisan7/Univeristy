#include "Song.h"

Song::Song(const std::string& title, const std::string& artist, int duration) :title{ title }, artist{ artist }, duration{ duration }
{}

Song::Song():title{""}, artist{""}, duration{0}
{
}

std::string Song::getArtist() const
{
	return this->artist;
}
