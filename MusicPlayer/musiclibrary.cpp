#include "musiclibrary.h"

MusicLibrary::MusicLibrary()
{
    songs = std::forward_list<Song*>(0);
}

MusicLibrary::~MusicLibrary() {
    songs.clear();
}

void MusicLibrary::addSong(Song * newSong) {
    songs.push_front(newSong);
}

Song * MusicLibrary::getSong(std::string title) const
{
    std::forward_list<Song*>::const_iterator iterator = songs.begin();
    for (; iterator != songs.end(); ++iterator) {
       //qInfo((*iterator)->url.c_str());
        if((*iterator)->title.compare(title) == 0) { //found matching Song w/ title
            return *iterator;
        }
    }
    return nullptr;;
}
