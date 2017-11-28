#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <forward_list>
#include "song.h"
#include "artist.h"
#include "json.hpp"

#define SongVector std::forward_list<const Song*>

/**
 * @brief MusicLibrary --- represents a collection of all music loaded from some physical location.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   11/28/2017
 */
class MusicLibrary
{
public:
    //Methods:
    MusicLibrary();
    /**
     * @brief Create a MusicLibrary from its string representation.
     * @param representation JSON string representation.
     */
    MusicLibrary(const std::string representation);
    ~MusicLibrary();

    /**
     * @brief Add a Song to the library.
     * @param newSong Ptr. to song to add.
     */
    void addSong(const Song * const newSong);

    /**
     * @brief Find/return an existing Song in the library, if it exists.
     * @param title Title of Song to search for.
     * @return ptr. of Song found, or nullptr if not found.
     */
    const Song * getSong(const std::string title) const;

    std::string toString() const;

private:
    //Vars:
    SongVector songs;      //List of Songs in library
    //Artist ** artist;   //array of ptrs. to Artists in lib.
    //Playlist ** playlists; //array of ptrs to Playlists
};

void to_json(nlohmann::json &j, const SongVector &l);
void from_json(const nlohmann::json &j, SongVector &l);

void to_json(nlohmann::json &j, const MusicLibrary &l);
void from_json(const nlohmann::json &j, MusicLibrary &l);


#endif // MUSICLIBRARY_H
