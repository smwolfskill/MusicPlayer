#include "album.h"

const Album::AlbumCompare Album::albumCmp = Album::AlbumCompare();

Album::Album(const std::string name, int released)
{
    this->name = name;
    this->released = released;
    songs = SongVector(0);
}

bool Album::operator <(const Album &other)
{
    if(strcmp(name.c_str(), other.name.c_str()) < 0) {
        return true;
    }
    return false;
}
