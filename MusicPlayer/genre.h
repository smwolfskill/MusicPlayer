#ifndef GENRE_H
#define GENRE_H

#include "song.h"
#include "cvector.h"

/**
 * @brief Genre --- Represents the musical genre of a Song.
 * @author      Scott Wolfskill
 * @created     12/04/2017
 * @last_edit   08/17/2018
 */
class Genre
{
#define GenreVector CVector<Genre*, std::string>
public:
    /**
     * @brief Map Genre A to be equivalent w/ string b <=> A.name == b
     */
    class GenreCompare : public Compare<Genre*, std::string> {
    public:
        virtual bool equiv(Genre* const &genre, const std::string &name) const override{
            return genre->name == name;
        }
    };

    //Vars:
    static const GenreCompare genreCmp;
    std::string name;
    SongVector songs; //songs in genre

    //Methods:
    /**
     * @brief Compare two Genres alphabetically.
     * @return true if a's name is alphabetically before b's.
     */
    static bool compareBy_name(Genre * const a, Genre * const b);

    Genre(const std::string name);

    /**
     * @brief Sort songs via a binary comparison function pointer.
     */
    void sortSongs(bool (*compare)(Song * const a, Song * const b));

};

#endif // GENRE_H
