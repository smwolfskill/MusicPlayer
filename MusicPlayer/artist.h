#ifndef ARTIST_H
#define ARTIST_H

#include "album.h"
#include "cvector.h"
#include "compare.h"

/**
 * @brief Artist --- Represents the author of some Album(s).
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   12/05/2017
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
    Artist(const std::string name);
    ~Artist();

    /**
     * @brief For sorting purposes, define a < b if a.name is alphabetically before b.name.
     * @param other Artist to compare with.
     * @return true if a's name is alphabetically before b's.
     */
    bool operator <(const Artist &other);

    //std::string toString() const;

};

#endif // ARTIST_H
