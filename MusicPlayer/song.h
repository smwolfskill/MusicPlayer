#ifndef SONG_H
#define SONG_H

#include <QString>

/**
 * @brief Song --- represents a Song in the music library.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   11/14/2017
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
    Song(std::string url, std::string title, std::string artist,
         std::string album, std::string genre, unsigned int year);
    bool Equals(const Song *const other) const;
    QString toString() const;
};

#endif // SONG_H
