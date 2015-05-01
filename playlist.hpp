#ifndef WHALE_PLAYLIST_H

#define WHALE_PLAYLIST_H

#include <string>
#include <vector>

using namespace std;

struct track
{
 string path,filename,artist,title,tags;
 int i;
};

typedef vector<track> playlist_type;
typedef vector<track>::iterator playlist_iterator;

class playlist  {
    private:
        playlist_type tracks;
        int current;
    public:
        void enqueue(string fn);
        void getTagForTrack(int); //working title
        void shuffle();
        size_t getSize();
    
    
};

#endif