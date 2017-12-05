#include "artist.h"

const Artist::ArtistCompare Artist::artistCmp = ArtistCompare();

Artist::Artist(const std::string name)
{
    this->name = name;
    albums = AlbumVector(0);
    Album * single = new Album("Single");
    albums.push_back(single); //will be list of songs by this Artist that have missing album info, if any.
}

Artist::~Artist()
{
    delete albums[0];
    albums.clear();
}

bool Artist::operator <(const Artist &other)
{
    if(strcmp(name.c_str(), other.name.c_str()) < 0) {
        return true;
    }
    return false;
}
