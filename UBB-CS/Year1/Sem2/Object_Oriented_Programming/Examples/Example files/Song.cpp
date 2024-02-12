#include "Song.h"
#include <Windows.h>
#include <shellapi.h>
#include "Utils.h"
#include <iostream>
#include <vector>

using namespace std;

Song::Song(): title(""), artist(""), duration(Duration()), source("") {}

Song::Song(const std::string& artist, const std::string& title, const Duration& duration, const std::string& source)
{
	this->artist = artist;
	this->title = title;
	this->duration = duration;
	this->source = source;
}

void Song::play()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getSource().c_str(), NULL, SW_SHOWMAXIMIZED);
}


// example of line in file: 
// Pink Floyd,Comfortably numb,6:53,https://www.youtube.com/watch?v=_FrOQC-zEog

istream & operator>>(istream & is, Song & s)
{
	// use reading with getline and then tokenisation if you want to validate the number of tokens

	if (is.eof())
		is.setstate(ios_base::failbit); // operator bool returns true for eof => enforce false to terminate the loop
	else
	{
		getline(is, s.artist, ',');
		getline(is, s.title, ',');
		Duration d{};
		string min, sec;
		getline(is, min, ':');
		getline(is, sec, ',');
		d.setMinutes(stod(min)); // ! validation - check is min is double
		d.getSeconds(stod(sec)); // ! validation - check is sec is double
		s.duration = d;
		getline(is, s.source, '\n');
	}
	return is;
}

ostream & operator<<(ostream & os, const Song & s)
{
	os << s.artist << "," << s.title << "," << s.duration.getMinutes() << ":" << s.duration.getSeconds() << "," << s.source << "\n";
	return os;
}
