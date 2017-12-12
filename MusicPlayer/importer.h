#ifndef IMPORTER_H
#define IMPORTER_H

#include "musiclibrary.h"
#include "metadata.h"
#include "vector.h"
#include <fstream>


/**
 * @brief Importer --- non-instantiable class for importing a MusicLibrary from a location on the disk.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   12/10/2017
 */
class Importer
{
public:
    /**
     * @brief Parse a file line-by-line and return its contents in order.
     * @param fileUrl Absolute path of file to read.
     * @return Pointer to list of strings of fileUrl contents, or nullptr if not found.
     */
    static StringVector * readLines(const std::string fileUrl);

    /**
     * @brief Write to a file line-by-line, creating new file if doesn't exist
     *        and overwriting existing contents.
     * @param fileUrl Absolute path of file to write to.
     * @param lines Ptr. to vector list of lines to sequentially write to file.
     * @param start 0-based index to start at in lines.
     * @return false if error encountered.
     */
    static bool saveLines(const std::string fileUrl, const Vector<std::string> * const lines, unsigned start = 0);

    /**
     * @brief Append to the end of a file line-by-line, not overwriting existing contents.
     * @param fileUrl Absolute path of file to write to.
     * @param lines Ptr. to vector list of lines to sequentially write to file.
     * @param start 0-based index to start at in lines.
     * @return false if error encountered.
     */
    static bool appendLines(const std::string fileUrl, const Vector<std::string> * const lines, unsigned start = 0);

private:
    //Methods:
    Importer() {} //don't allow instantiation
    static bool saveTo(std::ofstream &openStream, const Vector<std::string> * const lines, unsigned start);
};

#endif // IMPORTER_H
