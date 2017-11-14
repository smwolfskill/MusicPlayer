#ifndef ARTIST_H
#define ARTIST_H

#include <QString>
#include <album.h>

/**
 * @brief Artist --- Represents the author of some Album(s).
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   11/13/2017
 */
class Artist
{
public:
    //Vars:
    QString name;
    Album ** albums;    //array of ptrs. to Albums this Artist authored.
    //TODO: Picture (rand. album cover?)

    //Methods:
    Artist();
    ~Artist();
    QString toString() const;

};

#endif // ARTIST_H
