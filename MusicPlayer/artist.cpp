#include "artist.h"

const Artist::ArtistCompare Artist::artistCmp = ArtistCompare();

bool Artist::compareBy_name(const Artist * const a, const Artist * const b)
{
    if(strcmp(a->name.c_str(), b->name.c_str()) < 0) {
        return true;
    }
    return false;
}

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
