#include <iostream>
#include "DynamicVector.h"
#include "LinkedList.h"
#include "Song.h"
using namespace std;
int main()
{
    List<Song>* L;
    cout << "What do you want to use?\n 1. Dynamic vector\n 2. Linked list\n";
    int option;
    cin >> option;
    if (option == 1) {
        L = new DynamicVector<Song>();
    }
    else if (option == 2) {
        L = new LinkedList<Song>();
    }
    else {
        cout << "You're stupid.\n";
        return 0;
    }
    while (true) {
        cout << "1. add song\n2. show all songs\n3.play song by index\n4. exit\n";
        cin >> option;
        if (option == 1) {
            string title, artist, source;
            int minutes, seconds;
            cout << "Title:";
            cin >> title;
            cout << "Artist:";
            cin >> artist;
            cout << "Source:";
            cin >> source;
            cout << "Minutes:";
            cin >> minutes;
            cout << "Seconds:";
            cin >> seconds;
            Song a(artist, title, Duration(minutes, seconds), source);
            L->add(a);
        }
        else if (option == 2)
        {
            for (int i = 0;i < L->getSize();i++)
            {
                cout << (*L)[i].getTitle() << endl;
            }
        }
        else if (option == 3)
        {
            int listSize = L->getSize(), index;
            cout << "Give song index (between 0 and " << listSize - 1 << "): ";
            cin >> index;
            if (index < 0 || index >= listSize)
            {
                cout << "Wrong index!\n";
            }
            else
            {
                Song s = (*L)[index];
                s.play();
            }
        }
        else if (option == 4)
        {
            delete L;
            break;
        }
    }
    return 0;
}

