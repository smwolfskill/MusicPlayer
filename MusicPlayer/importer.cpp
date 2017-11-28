#include "importer.h"
#include <QString>
#include <string>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <fstream>
//TabLib includes:
#include <mpegfile.h>
#include <attachedpictureframe.h>
#include <id3v2tag.h>

using namespace std;

MusicLibrary * Importer::importLibrary(const string directoryUrl) {
    qInfo("Begin import from ");
    MusicLibrary * lib = new MusicLibrary();
    if(importLibrary(directoryUrl, lib)) {
        qInfo("Finished import successfully.");
    }
    return lib;
}

bool Importer::importLibrary(const string directoryUrl, MusicLibrary * const existingLibrary) {
    qInfo(directoryUrl.c_str());

    //1. Find all sound files in directoryUrl
    DIR * dir = opendir(directoryUrl.c_str());
    if(dir != nullptr){
        struct dirent * curEntry;
        errno = 0;
        //string dirUrlStr(directoryUrl);
        while(curEntry = readdir(dir)){
            if(strcmp(curEntry->d_name, ".") != 0 && strcmp(curEntry->d_name, "..") != 0) {
                //Actual file in directoryUrl
                qInfo(curEntry->d_name);

                string curEntryPath = directoryUrl + "/" + curEntry->d_name;
                switch(curEntry->d_type) {
                    case DT_DIR: //Recursively add to library from this subdirectory.
                        importLibrary(curEntryPath, existingLibrary);
                        break;
                    case DT_REG: {
                        TagLib::MPEG::File curFile(curEntryPath.c_str());
                        if(curFile.hasAPETag() || curFile.hasID3v1Tag() || curFile.hasID3v2Tag()) {
                            TagLib::Tag * tag = curFile.tag();
                            qInfo(tag->artist().toCString());
                            qInfo(tag->album().toCString());
                            qInfo(tag->genre().toCString()); //char* form
                            //qInfo(tag->genre().to8Bit().c_str()); //std::string -> char* form (if string is useful)
                            Song * song = new Song(curEntryPath, tag->title().to8Bit(), tag->artist().to8Bit(),
                                                 tag->album().to8Bit(), tag->genre().to8Bit(), tag->year());
                            existingLibrary->addSong(song);
                        }
                        break;
                        }
                    case DT_UNKNOWN:
                        qWarning("importLibrary: Unknown file type encountered!");
                        break;
                }

            }
        }
        closedir(dir);
        if(errno != 0) {
            qErrnoWarning(errno, "importLibrary: reading dir failed!");
            return false; //failure
        }
    } else {
        qWarning("importLibrary: dir not found!");
    }
    /*TagLib::MPEG::File audioFile(url);
    TagLib::ID3v2::Tag *tag = audioFile.ID3v2Tag(true);*/
    return true; //success
}
