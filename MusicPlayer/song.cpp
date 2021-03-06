#include "song.h"
#include <string>

QMediaPlaylist * Song::SongVectorToQMediaPlaylist(const SongVector &songs)
{
    if(songs.size() == 0) { //no songs in playlist
        return nullptr;
    }
    QMediaPlaylist * qPlaylist = new QMediaPlaylist();
    for(unsigned i = 0; i < songs.size(); i++) {
        qPlaylist->addMedia(QUrl(songs[i]->url.c_str()));
    }
    return qPlaylist;
}

Song::Song(std::string url, std::string name, std::string artist,
                       std::string album, std::string genre, unsigned int trackNum, unsigned int year) {
    this->url = url;
    this->title = name;
    this->artist = artist;
    this->album = album;
    this->genre = genre;
    this->trackNum = trackNum;
    this->year = year;
}

Song::Song(const std::string representation)
{
    nlohmann::json song = nlohmann::json::parse(representation);
    *this = song;
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
    if(trackNum != other->trackNum) {
        return false;
    }
    if(year != other->year) {
        return false;
    }
    return true;
}

bool Song::operator <(const Song &other) const
{
    if(strcmp(title.c_str(), other.title.c_str()) < 0) {
        return true;
    }
    return false;
}

std::string Song::toString() const
{
    nlohmann::json song = *this;
    return song.dump();
}

void to_json(nlohmann::json& j, const Song &s) {
    j = nlohmann::json{{"url", s.url}, {"title", s.title}, {"artist", s.artist}, {"album", s.album},
             {"genre", s.genre}, {"trackNum", s.trackNum}, {"year", s.year}, {"playCount", s.playCount}};
}

void from_json(const nlohmann::json &j, Song &s) {
    s.url = j.at("url").get<std::string>();
    s.title = j.at("title").get<std::string>();
    s.artist = j.at("artist").get<std::string>();
    s.album = j.at("album").get<std::string>();
    s.genre = j.at("genre").get<std::string>();
    s.trackNum = j.at("trackNum").get<unsigned int>();
    s.year = j.at("year").get<unsigned int>();
    s.playCount = j.at("playCount").get<int>();
}
