#ifndef SONG_H
#define SONG_H

#include "json.hpp"
#include <QString>

/**
 * @brief Song --- represents a Song in the music library.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   11/28/2017
 */
class Song
{
public:
    //Vars:
    std::string url;    //absolute path of song sound file
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    unsigned int year;  //year released
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

    std::string toString() const;


};

void to_json(nlohmann::json &j, const Song &s);
void from_json(const nlohmann::json &j, Song &s);

#endif // SONG_H
