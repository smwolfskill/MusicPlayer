#ifndef ARTIST_H
#define ARTIST_H

#include "album.h"
#include "cvector.h"
#include "compare.h"

/**
 * @brief Artist --- Represents the author of some Album(s).
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   08/17/2018
 */
class Artist
{
#define ArtistVector CVector<Artist*, std::string>
public:
    /**
     * @brief Map Artist A to be equivalent w/ string b <=> A.name == b
     */
    class ArtistCompare : public Compare<Artist*, std::string> {
    public:
        virtual bool equiv(Artist* const &artist, const std::string &name) const override {
            return artist->name == name;
        }
    };

    //Vars:
    static const ArtistCompare artistCmp;
    std::string name;

    /* Format: albums[0] is list of songs by this Artist that have missing album info,
     * i.e. album "Single".  */
    AlbumVector albums;
    //TODO: Picture (rand. album cover?)



    //Methods:
    /**
     * @brief Compare two Artists alphabetically.
     * @return true if a's name is alphabetically before b's.
     */
    static bool compareBy_name(Artist * const a, Artist * const b);

    Artist(const std::string name);
    ~Artist();

    /**
     * @brief Sort albums via a binary comparison function pointer; chronological by default.
     */
    void sortAlbums(bool (*compare)(Album * const, Album * const) = Album::compareBy_year);

    //std::string toString() const;

};

#endif // ARTIST_H
