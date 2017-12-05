#include "musiclibrary.h"
#include <dirent.h>
//TabLib includes:
#include <mpegfile.h>
#include <attachedpictureframe.h>
#include <id3v2tag.h>

const std::string MusicLibrary::UNKNOWN_TITLE = "N/A";
const std::string MusicLibrary::UNKNOWN_ARTIST = "Unknown";
const std::string MusicLibrary::UNKNOWN_GENRE = "Unknown";


MusicLibrary::MusicLibrary()
{
    songs = SongVector(0);
    artists = ArtistVector(0);
    albums = AlbumVector(0);
    genres = GenreVector(0);

    Artist * unknownArtist = new Artist(UNKNOWN_ARTIST);
    artists.push_back(unknownArtist); //will hold ptrs to songs w/ blank artist info
    Genre * unknownGenre = new Genre(UNKNOWN_GENRE);
    genres.push_back(unknownGenre); //will hold ptrs to any songs w/ blank genre info
}

MusicLibrary::MusicLibrary(const std::string representation)
{
    nlohmann::json lib = nlohmann::json::parse(representation);
    *this = lib;
}

MusicLibrary::~MusicLibrary() {
    songs.clear();
}

bool MusicLibrary::addToLibrary(const std::string directoryUrl)
{
    using namespace std;
    //1. Find all sound files in directoryUrl
    DIR * dir = opendir(directoryUrl.c_str());
    if(dir == nullptr) {
        return false;
    }
    struct dirent * curEntry;
    errno = 0;

    while(curEntry = readdir(dir)){ //read all links in dir
        if(strcmp(curEntry->d_name, ".") != 0 && strcmp(curEntry->d_name, "..") != 0) {
            //Actual file in directoryUrl
            //qInfo(curEntry->d_name);
            string curEntryPath = directoryUrl + "/" + curEntry->d_name;
            switch(curEntry->d_type) {
            case DT_DIR: //Recursively add to library from this subdirectory.
                addToLibrary(curEntryPath);
                break;
            case DT_REG: {
                TagLib::MPEG::File curFile(curEntryPath.c_str());
                if(curFile.hasAPETag() || curFile.hasID3v1Tag() || curFile.hasID3v2Tag()) {
                    TagLib::Tag * tag = curFile.tag();
                    //qInfo(tag->artist().toCString());
                    //qInfo(tag->album().toCString());
                    //qInfo(tag->genre().toCString()); //char* form
                    //qInfo(tag->genre().to8Bit().c_str()); //std::string -> char* form (if string is useful)
                    Song * song = new Song(curEntryPath, tag->title().to8Bit(), tag->artist().to8Bit(),
                                           tag->album().to8Bit(), tag->genre().to8Bit(), tag->year());
                    addSong(song);
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
    /*TagLib::MPEG::File audioFile(url);
    TagLib::ID3v2::Tag *tag = audioFile.ID3v2Tag(true);*/
    return true; //success
}

void MusicLibrary::addSong(Song * newSong) {
    //1. Fill in blank info and push to songs vector.
    if(newSong->title == "") {
        newSong->title = UNKNOWN_TITLE;
    }
    if(newSong->artist == "") {
        newSong->artist = UNKNOWN_ARTIST;
    }
    if(newSong->genre == "") {
        newSong->genre = UNKNOWN_GENRE;
    }
    songs.push_back(newSong); //add to songs list

    int artistIndex = artists.find(Artist::artistCmp, newSong->artist);
    int genreIndex = genres.find(Genre::genreCmp, newSong->genre);
    int albumIndex = -1;
    if(newSong->album != "") {
        albumIndex = albums.find(Album::albumCmp, newSong->album);
    }
    Artist * artist;
    Album * album;
    Genre * genre;

    //2.1 Check if artist exists in library
    if(artistIndex == -1) { //not found
        artist = new Artist(newSong->artist);
        artists.push_back(artist);
    } else {
        artist = artists[artistIndex];
    }

    //2.2 Check if album exists in lib
    if(albumIndex == -1) { //not found
        if(newSong->album == "") {
            album = artist->albums[0]; //artist's "Single" album
            newSong->album = album->name;
        } else {
            album = new Album(newSong->album);
            albums.push_back(album);
        }
    } else {
        album = albums[albumIndex];
    }

    //2.3 Check if genre exists in lib
    if(genreIndex == -1) { //not found
        genre = new Genre(newSong->artist);
        genres.push_back(genre);
    } else {
        artist = artists[artistIndex];
    }

    //3. Link the pieces together
    genre->songs.push_back(newSong);
    album->songs.push_back(newSong);
    //add newSong's album to newSong's artist if not present already
    if(artist->albums.find(Album::albumCmp, newSong->album) == -1) {
        artist->albums.push_back(album);
    }
    //songs.find(newSong);
    //artist->albums.contains(album);
}

Song * MusicLibrary::getSong(const std::string title) const
{
    //TODO: Change to be a search query for fields containing substring (title), & return result list.
    Vector<Song *>::const_iterator iterator = songs.begin();
    for (; iterator != songs.end(); ++iterator) {
       //qInfo((*iterator)->url.c_str());
        if((*iterator)->title.compare(title) == 0) { //found matching Song w/ title
            return *iterator;
        }
    }
    return nullptr;
}

/*void MusicLibrary::sortLibrary()
{

}*/

void to_json(nlohmann::json &j, const Vector<Song *> &l)
{
    using namespace std;
    string repr = "{{\"elements\", {";
    Vector<Song *>::const_iterator iterator = l.begin();
    repr += (*iterator)->toString(); //1st element
    iterator++;
    for(; iterator != l.end(); ++iterator) { //remaining elements
        repr += string(",") + (*iterator)->toString();
    }
    repr += "}}}";
    j = nlohmann::json::parse(repr);
}

void from_json(const nlohmann::json &j, Vector<Song *> &l)
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
