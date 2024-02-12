#pragma once
#include <string>

class Song
{

private:

	std::string title, artist;
	int duration;

public:

	Song(const std::string& title, const std::string &artist, int duration);

	Song();

	std::string getArtist()const;

	inline std::string getTitle() const { return this->title; }



};

