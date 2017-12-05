#ifndef METADATA_H
#define METADATA_H

#include "vector.h"
#include <string>

/**
 * @brief Metadata --- Holds information saved/loaded to/from metadata folder,
 *                     such as paths of music libraries to laod.
 * @author      Scott Wolfskill
 * @created     12/04/2017
 * @last_edit   12/04/2017
 */
class Metadata
{
public:
    //Vars:
    static const std::string LIBRARY_PATHS_FILENAME; //default name of file holding library paths to load

    //Format: 1st element is name of file in metadata folder to save/load from. The rest is data.
    Vector<std::string> * libraryPaths; //["filename", "libraryPath1", ...]

    //Methods:
    /**
     * @brief Create Metadata by importing from a directory, with all default filenames.
     * @param directory Absolute path of Metadata directory.
     */
    Metadata(const std::string directory) : Metadata(directory, LIBRARY_PATHS_FILENAME) {}

    /**
     * @brief Create Metadata by importing from a directory.
     * @param directory Absolute path of Metadata directory.
     * @param libPaths_filename Name of file containing absolute library paths to load separated by newline.
     */
    Metadata(const std::string directory, const std::string libPaths_filename);

    bool saveMetadata() { return saveMetadata(dir); }

    /**
     * @brief Save Metadata to a directory on the disk.
     * @param directory Absolute path of directory to save files in.
     *        Overwrites any existing metadata in that directory.
     * @return false if error encountered.
     */
    bool saveMetadata(const std::string directory) const;

private:
    //Vars:
    std::string dir; //metadata directory that was loaded from

    //Methods:
    /**
     * @brief importFrom
     * @param directory Absolute Metadata directory path.
     * @param libPaths_filename Name of file containing absolute library paths to load separated by newline.
     * @return 1: success; 0: libPaths_filename not found; -1: directory not found.
     */
    int importFrom(const std::string directory, const std::string libPaths_filename);
};

#endif // METADATA_H
