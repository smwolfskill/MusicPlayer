#include "song.h"
#include <string>

Song::Song(std::string url, std::string name, std::string artist,
                       std::string album, std::string genre, unsigned int year) {
    this->url = url;
    this->title = name;
    this->artist = artist;
    this->album = album;
    this->genre = genre;
    this->year = year;
}

bool Song::Equals(const Song *const other) const
{
    if(url.compare(other->url) != 0) {
        return false;
    }
    if(title.compare(other->title) != 0) {
        return false;
    }
    if(artist.compare(other->artist) != 0) {
        return false;
    }
    if(album.compare(other->album) != 0) {
        return false;
    }
    if(genre.compare(other->genre) != 0) {
        return false;
    }
    if(year != other->year) {
        return false;
    }
    return true;
}

QString Song::toString() const {

}
