#include "DynamicVector.h"
#include "Song.h"
#include <crtdbg.h>
#include <string>
#include <iostream>
#include <assert.h>
#include "Service.h"

using namespace std;

int main()
{
	{
		DynamicVector v1{};

		/*DynamicVector v2 = v1;

		DynamicVector v3{};
		v3 = v1;*/

		Song s{ "song_1", "artist_1", 100 };
		Song s2{};

		v1.add(s);
		v1.add(s2);

		assert(v1.getSize() == 2);

		Repository repo{};
		Service serv{ repo };
		// repo.addSong(Song{ "a", "b", 2 });
		serv.addSong("title1", "artist1", 100);
		serv.addSong("title2", "artist2", 200);
		assert(serv.getSize() == 2);
	}

	

	

	_CrtDumpMemoryLeaks();

	return 0;
}