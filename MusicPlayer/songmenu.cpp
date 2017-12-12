#include "songmenu.h"

SongMenu::SongMenu(const QObject *signalReceiver,
                   const char *playOnceSlot, const char *playNextSlot,
                   const char *playLastSlot, const char *playAllSlot,
                   const char *addToPlaylistSlot)
{
    this->addAction(tr("Play Once"), signalReceiver, playOnceSlot);
    this->addAction(tr("Play Next"), signalReceiver, playNextSlot);
    this->addAction(tr("Play Last"), signalReceiver, playLastSlot);
    this->addAction(tr("Play All"), signalReceiver, playAllSlot);
    this->addAction(tr("Add to Playlist..."), signalReceiver, addToPlaylistSlot);
}
