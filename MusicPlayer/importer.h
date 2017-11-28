#ifndef IMPORTER_H
#define IMPORTER_H

#include "musiclibrary.h"

/**
 * @brief Importer --- non-instantiable class for importing a MusicLibrary from a location on the disk.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   11/14/2017
 */
class Importer
{
public:
    /**
     * @brief Import a new MusicLibrary from a directory (and all subdirs) on the disk.
     * @param directoryUrl Absolute path of directory to import from.
     * @return Allocated ptr. to MusicLibrary. Caller must de-allocate.
     */
    static MusicLibrary * importLibrary(const std::string directoryUrl);

    /**
     * @brief Import and add to an existing MusicLibrary from a directory (and all subdirs) on the disk.
     * @param directoryUrl Absolute path of directory to import from.
     * @param existingLibrary Allocated ptr. to MusicLibrary to add onto.
     * @return true if success; false otherwise.
     */
    static bool importLibrary(const std::string directoryUrl, MusicLibrary * const existingLibrary);

private:
    Importer() {} //don't allow instantiation

};

#endif // IMPORTER_H
