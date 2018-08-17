#include "genre.h"

const Genre::GenreCompare Genre::genreCmp = Genre::GenreCompare();

bool Genre::compareBy_name(const Genre * const a, const Genre * const b)
{
    if(strcmp(a->name.c_str(), b->name.c_str()) < 0) {
        return true;
    }
    return false;
}

Genre::Genre(const std::string name)
{
    this->name = name;
    songs = SongVector(0);
}
