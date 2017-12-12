#ifndef PLAYLISTMENU_H
#define PLAYLISTMENU_H

#include <QMenu>

/**
 * @brief PlaylistMenu --- Represents a context menu for various Playlist actions (create new, etc.)
 * @author      Scott Wolfskill
 * @created     12/11/2017
 * @last_edit   12/11/2017
 */
class PlaylistMenu : public QMenu
{
public:
    PlaylistMenu(const QObject * signalReceiver, const char * renameSlot,
             const char * copySlot, const char * createNewSlot);
};

#endif // PLAYLISTMENU_H
