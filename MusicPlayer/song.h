#ifndef SONG_H
#define SONG_H

#include "vector.h"
#include "json.hpp"
#include <QString>

/**
 * @brief Song --- represents a Song in the music library.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   12/05/2017
 */
class Song
{
//#define SongVector CVector<Song*, std::string>
#define SongVector Vector<Song*>
public:
    /**
     * @brief Map Song A to be equivalent w/ string b <=> A.title == b
     */
    /*class SongCompare : public Compare<Song, std::string> {
    public:
        static bool equiv(Song song, std::string name) {
            return song.title == name;
        }
    };*/

    //Vars:
    std::string url;    //absolute path of song sound file
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    unsigned year;  //year released
    int playCount;

    //Methods:
    Song() {}
    Song(std::string url, std::string title, std::string artist,
         std::string album, std::string genre, unsigned int year);
    /**
     * @brief Create a Song from its string representation.
     * @param representation JSON string representation.
     */
    Song(const std::string representation);

    bool Equals(const Song * const other) const;

    /**
     * @brief For sorting purposes, define a < b if a.title is alphabetically before b.title.
     * @param other Song to compare with.
     * @return true if a's title is alphabetically before b's.
     */
    bool operator <(const Song & other) const;

    std::string toString() const;

};

void to_json(nlohmann::json &j, const Song &s);
void from_json(const nlohmann::json &j, Song &s);

#endif // SONG_H
