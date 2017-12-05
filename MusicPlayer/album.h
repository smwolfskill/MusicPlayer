#ifndef ALBUM_H
#define ALBUM_H

#include "song.h"
#include "cvector.h"

/**
 * @brief Album --- represents an Album containing a list of songs released together by an Artist.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   12/04/2017
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
     * @brief Create empty Album with name, release date.
     * @param name Album name.
     * @param released Year released. Default -1 means unknown or N/A.
     */
    Album(const std::string name, int released = -1);

    /**
     * @brief For sorting purposes, define a < b if a.name is alphabetically before b.name.
     * @param other Album to compare with.
     * @return true if a's name is alphabetically before b's.
     */
    bool operator <(const Album &other);
    //std::string toString() const;

};

#endif // ALBUM_H
