#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include "cvector.h"
#include "song.h"
#include "artist.h"
#include "album.h"
#include "genre.h"
#include "json.hpp"

/**
 * @brief MusicLibrary --- represents a collection of all music loaded from some physical location.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   12/04/2017
 */
class MusicLibrary
{
public:
    //Vars:
    static const std::string UNKNOWN_TITLE;
    static const std::string UNKNOWN_ARTIST;
    static const std::string UNKNOWN_GENRE;

    SongVector songs;
    ArtistVector artists;
    AlbumVector albums;
    GenreVector genres;

    //Methods:
    MusicLibrary();
    /**
     * @brief Create a MusicLibrary from its string representation.
     * @param representation JSON string representation.
     */
    MusicLibrary(const std::string representation);
    ~MusicLibrary();

    /**
     * @brief Import and add (append) to this MusicLibrary from a directory recursively on the disk.
     * @param directoryUrl Absolute path of directory to import from.
     * @param existingLibrary Allocated ptr. to MusicLibrary to add onto.
     * @return "" if success; else error message.
     */
    std::string addToLibrary(const std::string directoryUrl);

    /**
     * @brief Add a Song to the library.
     * @param newSong Ptr. to song to add.
     */
    void addSong(Song * newSong);

    /**
     * @brief Find/return an existing Song in the library, if it exists.
     * @param title Title of Song to search for.
     * @return ptr. of Song found, or nullptr if not found.
     */
    Song * getSong(const std::string title) const; //TODO: outdated; return list of matches.

    /**
     * @brief Sort all relevant interior data structures.
     */
    //void sortLibrary(); //TODO: don't do this! Ensure that Vec's are sorted as we insert, else slowww.

    std::string toString() const;

};

void to_json(nlohmann::json &j, const Vector<Song *> &l);
void from_json(const nlohmann::json &j, Vector<Song *> &l);

void to_json(nlohmann::json &j, const MusicLibrary &l);
void from_json(const nlohmann::json &j, MusicLibrary &l);


#endif // MUSICLIBRARY_H
