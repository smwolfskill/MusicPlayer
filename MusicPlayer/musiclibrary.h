#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <forward_list>
#include "song.h"
#include "artist.h"
#include "playlist.h"

/**
 * @brief MusicLibrary --- represents a collection of all music loaded from some physical location.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   11/14/2017
 */
class MusicLibrary
{
public:
    //Methods:
    MusicLibrary();
    ~MusicLibrary();

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
    Song * getSong(std::string title) const;

private:
    //Vars:
    std::forward_list<Song*> songs;      //List of Songs in library
    //Artist ** artist;   //array of ptrs. to Artists in lib.
    //Playlist ** playlists; //array of ptrs to Playlists
};

#endif // MUSICLIBRARY_H
