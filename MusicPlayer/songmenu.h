#ifndef SONGMENU_H
#define SONGMENU_H

#include <QObject>
#include <QMenu>

/**
 * @brief SongMenu --- Represents a context menu for various Song actions.
 * @author      Scott Wolfskill
 * @created     12/11/2017
 * @last_edit   12/11/2017
 */
class SongMenu : public QMenu
{
public:
    SongMenu(const QObject * signalReceiver,
             const char * playOnceSlot, const char * playNextSlot,
             const char * playLastSlot, const char * playAllSlot,
             const char * addToPlaylistSlot);
};

#endif // SONGMENU_H
