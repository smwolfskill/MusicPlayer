#include "album.h"

const Album::AlbumCompare Album::albumCmp = Album::AlbumCompare();

bool Album::compareBy_name(const Album * const a, const Album * const b)
{
    if(strcmp(a->name.c_str(), b->name.c_str()) < 0) {
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
