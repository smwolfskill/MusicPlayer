#ifndef SONG_H
#define SONG_H

#include "vector.h"
#include "json.hpp"
#include <QString>
#include <QMediaPlaylist>

/**
 * @brief Song --- represents a Song in the music library.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   08/17/2018
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
    unsigned trackNum; //track number/order in album
    unsigned year;  //year released
    int playCount;

    //Methods:
    /**
     * @brief Get a QMediaPlaylist representation of a SongVector.
     * @param songVector
     * @return nullptr if no songs in SongVector, else QMediaPlaylist.
     */
    static QMediaPlaylist * SongVectorToQMediaPlaylist(const SongVector &songs);

    /**
     * @brief Compare two Song pointers by their title in alphabetical order.
     * @return true, if a's title is alphabetically before b's.
     */
    static bool compareBy_title(Song * const a, Song * const b);

    /**
     * @brief Compare two Song pointers by artist.
     * @return true, if a's artist is alphabetically before b's.
     */
    static bool compareBy_artist(Song * const a, Song * const b);

    /**
     * @brief Compare two Song pointers by album.
     * @return true, if a's album is alphabetically before b's.
     */
    static bool compareBy_album(Song * const a, Song * const b);

    /**
     * @brief Compare two Song pointers by genre.
     * @return true, if a's artist is alphabetically before b's.
     */
    static bool compareBy_genre(Song * const a, Song * const b);

    /**
     * @brief Compare two Song pointers by their trackNum in ascending order.
     * @return true, if a's trackNum is before b's.
     */
    static bool compareBy_trackNum(Song * const a, Song * const b);

    /**
     * @brief Compare two Song pointers chronologically by year released.
     * @return true, if a was released before b was.
     */
    static bool compareBy_year(Song * const a, Song * const b);

    Song() {}
    Song(std::string url, std::string title, std::string artist,
         std::string album, std::string genre, unsigned int trackNum, unsigned int year);
    /**
     * @brief Create a Song from its string representation.
     * @param representation JSON string representation.
     */
    Song(const std::string representation);

    bool Equals(const Song * const other) const;

    std::string toString() const;

};

void to_json(nlohmann::json &j, const Song &s);
void from_json(const nlohmann::json &j, Song &s);

#endif // SONG_H
