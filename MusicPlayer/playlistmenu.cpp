#include "playlistmenu.h"

PlaylistMenu::PlaylistMenu(const QObject *signalReceiver, const char * renameSlot,
                           const char *copySlot, const char *createNewSlot)
{
    this->addAction(tr("Rename"), signalReceiver, renameSlot);
    this->addAction(tr("Copy..."), signalReceiver, copySlot);
    this->addAction(tr("Create new Playlist..."), signalReceiver, createNewSlot);
}
