#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"
#include "musiclibrary.h"
#include <forward_list>
#include <string>

/**
 * @brief Playlist --- class representing a list of Songs in some particular order to be viewed/played in.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   11/27/2017
 */
class Playlist
{
public:
    //Vars:

    //Methods:
    Playlist(const std::string name, const SongVector songs, int length);

    /**
     * @brief Create a Playlist from its string representation.
     * @param representation String representation of a Playlist that was generated via toString().
     * @param lib Ptr. to Library containing Songs that are in this Playlist.
     */
    Playlist(const std::string representation, const MusicLibrary * const lib);

    void setName(const std::string newName);
    std::string getName() const { return name; }
    bool isModified() const { return modified; }
    int getSelected_index() const { return selected_index; }

    /**
     * @brief Get currently selected Song in the Playlist.
     * @return Pointer to Song.
     */
    const Song * getSelected() const;

    /**
     * @brief Move selected to next Song after currently selected song.
     * @return Pointer to next Song after selected. If at end, will loop back to beginning.
     */
    const Song * getNext();

    /**
     * @brief Select the first song in the Playlist, if any.
     */
    void goToFirst();

    /**
     * @brief Set current Song to be (toGoTo). If there's more than one, goes to first one.
     * @param toGoTo Ptr. to Song to go to in this Playlist.
     * @return true if (toGoTo) is in this Playlist; false otherwise.
     */
    bool goToSong(const Song * const toGoTo);

    bool containsSong(const Song * const song) const;

    /**
     * @brief Add a Song to the end of this Playlist.
     * @param toAdd Pointer to Song to add.
     */
    void addSong(const Song * const toAdd);

    /**
     * @brief Add a Song to the Playlist after (index).
     * @param index 0-based index; 0 is Playlist start. If -1, inserts at Playlist start.
     * @param toAdd Pointer to Song to add.
     * @return true if removed successfully. False if (index) out of range.
     */
    bool addSongAfter(int index, const Song * const toAdd);

    /**
     * @brief Remove a Song from the Playlist.
     * @param index 0-based index; 0 is Playlist start.
     * @return true if removed successfully. False if (index) out of range.
     */
    bool removeSongAt(int index);

    std::string toString() const;

private:
    //Vars:
    std::string name; //shall not contain linebreaks.
    bool modified;    //if true, has been modified (songs added/removed) since it was created.
    int length;       //length of Playlist: # elements in songs.
    int selected_index; //index of current song selected/playing in songs array.
    SongVector::const_iterator selected;
    SongVector songs;  //std::forward_list<const Song*> list of Ptrs. to Songs in Playlist.

    //Methods:
    /**
     * @brief getIteratorAt index of songs.
     * @param index 0-based index.
     * @param iteratorIndex Init. before calling. Will point to index of result. Usage optional.
     * @return Iterator.
     */
    SongVector::const_iterator getIteratorAt(const int &index, int * const iteratorIndex = nullptr) const;

    /**
     * @brief Return an iterator to where in songs list (song) is located, if exists.
     * @param song Ptr. of Song to find.
     * @param iteratorIndex Allocate before calling. Will be iterator location of (song).
     * @return index of (song) in songs, or -1 if not found.
     */
     int findSong(const Song * const song, SongVector::const_iterator * const location) const;

};

#endif // PLAYLIST_H
