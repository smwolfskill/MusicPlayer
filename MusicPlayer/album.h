#ifndef ALBUM_H
#define ALBUM_H

#include "song.h"
#include "cvector.h"

/**
 * @brief Album --- represents an Album containing a list of songs released together by an Artist.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   08/17/2018
 */
class Album
{
#define AlbumVector CVector<Album*, std::string>
public:
    /**
     * @brief Map Album A to be equivalent w/ string b <=> A.name == b
     */
    class AlbumCompare : public Compare<Album*, std::string> {
    public:
        virtual bool equiv(Album* const &album, const std::string &name) const override {
            return album->name == name;
        }
    };

    //Vars:
    static const AlbumCompare albumCmp;
    std::string name;
    int released; //-1 means N/A
    SongVector songs; //songs in album in chronological order
    //TODO: var. for picture (AlbumArtSmall.jpg).

    //Methods:
    /**
     * @brief Compare two Albums alphabetically.
     * @return true if a's name is alphabetically before b's.
     */
    static bool compareBy_name(Album * const a, Album * const b);

    /**
     * @brief Compare two Albums chronologically by release date.
     * @return true if a was released before b was.
     */
    static bool compareBy_year(Album * const a, Album * const b);

    /**
     * @brief Create empty Album with name, release date.
     * @param name Album name.
     * @param released Year released. Default -1 means unknown or N/A.
     */
    Album(const std::string name, int released = -1);

    /**
     * @brief Sort songs, in chronological order by default (by trackNum).
     */
    void sortSongs(bool (*compare)(Song * const, Song * const) = Song::compareBy_trackNum);

    //std::string toString() const;
};

#endif // ALBUM_H
