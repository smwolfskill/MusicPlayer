#ifndef ALBUM_H
#define ALBUM_H

#include <QString>
#include <QDate>
#include "song.h"

/**
 * @brief Album --- represents an Album containing a list of songs released together by an Artist.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   11/13/2017
 */
class Album
{
public:
    //Vars:
    QString name;
    QDate release;
    Song ** songs;  //array of ptrs. to Songs in album, in chronological order
    //TODO: var. for picture (AlbumArtSmall.jpg).

    //Methods:
    Album();
    QString toString() const;

};

#endif // ALBUM_H
