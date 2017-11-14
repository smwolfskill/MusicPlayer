#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <song.h>

/**
 * @brief Playlist --- class representing a list of Songs in some particular order to be viewed/played in.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   11/13/2017
 */
class Playlist
{
public:
    //Vars:
    Song ** songs;  //array of ptrs. to Songs in Playlist
    //TODO later

    //Methods:
    Playlist();
};

#endif // PLAYLIST_H
