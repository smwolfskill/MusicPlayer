#ifndef GENRE_H
#define GENRE_H

#include "song.h"
#include "cvector.h"

/**
 * @brief Genre --- Represents the musical genre of a Song.
 * @author      Scott Wolfskill
 * @created     12/04/2017
 * @last_edit   12/05/2017
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
    Genre(const std::string name);

    /**
     * @brief For sorting purposes, define a < b if a.name is alphabetically before b.name.
     * @param other Genre to compare with.
     * @return true if a's name is alphabetically before b's.
     */
    bool operator <(const Genre &other);
};

#endif // GENRE_H
