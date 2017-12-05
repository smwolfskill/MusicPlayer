#include "genre.h"

const Genre::GenreCompare Genre::genreCmp = Genre::GenreCompare();

Genre::Genre(const std::string name)
{
    this->name = name;
    songs = SongVector(0);
}

bool Genre::operator <(const Genre &other)
{
    if(strcmp(name.c_str(), other.name.c_str()) < 0) {
        return true;
    }
    return false;
}
