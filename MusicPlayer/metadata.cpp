#include "metadata.h"
#include "importer.h"
#include <dirent.h>

const std::string Metadata::LIBRARY_PATHS_FILENAME = "libraryPaths.txt";

Metadata::Metadata(const std::string directory, const std::string libPaths_filename)
{
    dir = directory;
    int result = importFrom(directory, LIBRARY_PATHS_FILENAME);
    if(result != 1) { //directory or library path not found.
        libraryPaths = nullptr;
    }
}

int Metadata::importFrom(const std::string directory, const std::string libPaths_filename)
{
    //1. Check if directory exists.
    DIR * d = opendir(directory.c_str());
    if(d == nullptr) { //failure: directory doesn't exist.
        return -1;
    }
    closedir(d);

    //2. Import libraryPaths metadata
    const std::string libPathsFilename = directory + "/" + libPaths_filename;
    Vector<std::string> * lines = Importer::readLines(libPathsFilename);
    if(lines == nullptr) { //failure: file doesn't exist
        return 0;
    }
    libraryPaths = lines;
    lines->insertBefore(0, libPaths_filename); //["filename", "lib1", ...] format

    return 1; //success
}

bool Metadata::saveMetadata(const std::string directory) const
{
    Importer::saveLines(directory + "/" + (*libraryPaths)[0], libraryPaths, 1); //don't include filename in output
}
