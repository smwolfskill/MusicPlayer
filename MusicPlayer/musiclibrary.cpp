#include "musiclibrary.h"

MusicLibrary::MusicLibrary()
{
    songs = SongVector(0);
}

MusicLibrary::MusicLibrary(const std::string representation)
{
    nlohmann::json lib = nlohmann::json::parse(representation);
    *this = lib;
}

MusicLibrary::~MusicLibrary() {
    songs.clear();
}

void MusicLibrary::addSong(const Song * const newSong) {
    songs.push_front(newSong);
    /*TODO: Create (ideally fast) data structure holding artist, album info to be updated when
      songs are added here. */
}

const Song * MusicLibrary::getSong(const std::string title) const
{
    //TODO: Change to be a search query for fields containing substring (title), & return result list.
    SongVector::const_iterator iterator = songs.begin();
    for (; iterator != songs.end(); ++iterator) {
       //qInfo((*iterator)->url.c_str());
        if((*iterator)->title.compare(title) == 0) { //found matching Song w/ title
            return *iterator;
        }
    }
    return nullptr;
}

void to_json(nlohmann::json &j, const SongVector &l)
{
    using namespace std;
    string repr = "{{\"elements\", {";
    SongVector::const_iterator iterator = l.begin();
    repr += (*iterator)->toString(); //1st element
    iterator++;
    for(; iterator != l.end(); ++iterator) { //remaining elements
        repr += string(",") + (*iterator)->toString();
    }
    repr += "}}}";
    j = nlohmann::json::parse(repr);
}

void from_json(const nlohmann::json &j, SongVector &l)
{

    //Song *const * arr; //array of const Song*
    //arr = j
    //l = j.at("elements").get<SongVector>;

}

void to_json(nlohmann::json &j, const MusicLibrary &l)
{

}

void from_json(const nlohmann::json &j, MusicLibrary &l)
{

}
