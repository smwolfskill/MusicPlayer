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
    if(year != other->year) {
        return false;
    }
    return true;
}

std::string Song::toString() const
{
    nlohmann::json song = *this;
    return song.dump();
}

void to_json(nlohmann::json& j, const Song &s) {
    j = nlohmann::json{{"url", s.url}, {"title", s.title}, {"artist", s.artist}, {"album", s.album},
             {"genre", s.genre}, {"year", s.year}, {"playCount", s.playCount}};
}

void from_json(const nlohmann::json &j, Song &s) {
    s.url = j.at("url").get<std::string>();
    s.title = j.at("title").get<std::string>();
    s.artist = j.at("artist").get<std::string>();
    s.album = j.at("album").get<std::string>();
    s.genre = j.at("genre").get<std::string>();
    s.year = j.at("year").get<unsigned int>();
    s.playCount = j.at("playCount").get<int>();
}
