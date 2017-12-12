#ifndef PLAYLISTITEMMENU_H
#define PLAYLISTITEMMENU_H

#include "songmenu.h"

/**
 * @brief PlaylistItemMenu --- Represents a context menu for various actions for Songs specifically in a Playlist.
 * @author      Scott Wolfskill
 * @created     12/11/2017
 * @last_edit   12/11/2017
 */
class PlaylistItemMenu : public SongMenu
{
public:
    PlaylistItemMenu(const QObject * signalReceiver,
                 const char * playOnceSlot, const char * playNextSlot,
                 const char * playLastSlot, const char * playAllSlot,
                 const char * addToPlaylistSlot, const char * removeFromPlaylistSlot)
                : SongMenu(signalReceiver, playOnceSlot, playNextSlot,
                           playLastSlot, playAllSlot, addToPlaylistSlot)
    {
        this->addAction(tr("Remove from Playlist"), signalReceiver, removeFromPlaylistSlot);
    }
};

#endif // PLAYLISTITEMMENU_H
