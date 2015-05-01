#include "playlist.hpp"

void playlist::enqueue(string fn) {
 track trk;
 trk.path=fn;
 trk.i=tracks.size()+1;
 //maybe also id3 here later
 tracks.push_back(trk);
}

size_t playlist::getSize() {
    return tracks.size();
}