#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"
#include "vector.h"
#include "musiclibrary.h"
#include <string>
#include <QMediaPlaylist>

/**
 * @brief Playlist --- class representing a list of Songs in some particular order to be viewed/played in.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   12/05/2017
 */
class Playlist
{
#define PlaylistVector Vector<Playlist*>
public:
    //TODO: make songs private if want to detect modification!
    //Vars:
    SongVector songs;  //list of Ptrs. to Songs in Playlist.

    //Methods:
    Playlist(const std::string name);

    /**
     * @brief Create a Playlist from its string representation.
     * @param representation String representation of a Playlist that was generated via toString().
     * @param lib Ptr. to Library containing Songs that are in this Playlist.
     */
    Playlist(const std::string representation, const MusicLibrary * const lib);

    void setName(const std::string newName);
    std::string getName() const { return name; }
    bool isModified() const { return modified; }
    int getSelected_index() const { return selected; }

    /**
     * @brief Get currently selected Song in the Playlist.
     * @return Pointer to Song, or nullptr if none selected.
     */
    Song * getSelected() const;

    /**
     * @brief Move selected to next Song after currently selected song. If at end, will loop back to beginning.
     * @param returnBeginning If at end: if returnBeginning true, will return 1st Song. Else, will return nullptr.
     * @return Pointer to next Song after selected.
     */
    Song * getNext(bool returnBeginning = false);

    /**
     * @brief Select the first song in the Playlist, if any.
     */
    void goToFirst();

    /**
     * @brief Set current Song to be (toGoTo). If there's more than one, goes to first one.
     * @param toGoTo Ptr. to Song to go to in this Playlist.
     * @return true if (toGoTo) is in this Playlist; false otherwise.
     */
    bool goToSong(Song * const toGoTo);

    /**
     * @brief Return remaining songs in list after and including selected. Starts at beginning if none selected.
     * @return SongVector to remaining songs, or nullptr if no songs in playlist.
     */
    SongVector getRemaining();

    std::string toString() const;

private:
    //Vars:
    std::string name; //shall not contain linebreaks.
    bool modified;    //if true, has been modified (songs added/removed) since it was created.
    int selected; //index of current song selected/playing in songs vector.

};

#endif // PLAYLIST_H
