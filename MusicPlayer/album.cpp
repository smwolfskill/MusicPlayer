#include "album.h"

const Album::AlbumCompare Album::albumCmp = Album::AlbumCompare();

bool Album::compareBy_name(Album * const a, Album * const b)
{
    if(strcmp(a->name.c_str(), b->name.c_str()) < 0) {
        return true;
    }
    return false;
}

bool Album::compareBy_year(Album * const a, Album * const b)
{
    if(a->released < b->released) {
        return true;
    }
    return false;
}

Album::Album(const std::string name, int released)
{
    this->name = name;
    this->released = released;
    songs = SongVector(0);
}

void Album::sortSongs(bool (*compare)(Song * const, Song * const))
{
    songs.sort(compare);
}
