#include "engine.h"
#include <QDir>
#include <QMediaPlaylist>

const std::string Engine::EXEC_PATH = QDir::currentPath().toStdString();


Engine::Engine()
{
    playlists = PlaylistVector(0);
    Playlist * sessionPlaylist = new Playlist("Now Playing"); //empty session playlist
    playlists.push_back(sessionPlaylist);
    metadata_path = EXEC_PATH + "/metadata/";
    player = new QMediaPlayer;
    metadata = nullptr;
    library = nullptr;
}

Engine::Engine(std::string metadata_path) {
    this->metadata_path = metadata_path;
    player = new QMediaPlayer;
    metadata = nullptr;
    library = nullptr;
}

Engine::~Engine() {
    //TODO: ensure save playlists, metadata on disk before this DTOR called
    playlists.clear();
    delete player;
    delete metadata;
    delete library;
}

bool Engine::loadAll() {
    if(!loadMetadata()) {
        return false; //no metadata exists, so nothing to load.
    }
    //1. Load all libraries specified in metadata libraryPaths.
    for(unsigned i = 1; i < metadata->libraryPaths->size(); i++) { //start after beginning ["filename", ..]
        loadLibrary((*metadata->libraryPaths)[i]);
    }
    //lib->sortLibrary(); //sort updated library
    return true;
}

bool Engine::loadMetadata()
{
    metadata = new Metadata(metadata_path);
    if(metadata->libraryPaths == nullptr) {
        return false;
    }
    return true;
}

bool Engine::saveMetadata()
{
    return metadata->saveMetadata();
}

bool Engine::addLibrary(const std::string directoryUrl)
{
    //1. Check if need to load metadata
    if(metadata == nullptr) {
        loadMetadata();
    }

    //2. Check if already loaded this library
    if(metadata->libraryPaths->contains(directoryUrl)) {
        return false; //already loaded
    }

    //3. Load library at directoryUrl
    metadata->libraryPaths->push_back(directoryUrl); //add to libraryPaths metadata
    if(!loadLibrary(directoryUrl)) {
        std::string warning = "Could not load library from '" + directoryUrl + "': does not exist.";
        qWarning(warning.c_str());
        return false;
    }

    //4. Sort updated library
    //lib->sortLibrary();
    return true;
}

bool Engine::loadLibrary(const std::string directoryUrl)
{
    //add library at directoryUrl to current library.
    //add directoryUrl to metadata list of libs we've imported from.
    if(library == nullptr) {
        library = new MusicLibrary();
    }
    return library->addToLibrary(directoryUrl);
}

void Engine::setVolume(int newVolume)
{
    //TODO: Make sure UI scale slider is logarithmic.
    player->setVolume(newVolume);
}

bool Engine::playSelected()
{
    Song * selected = playlists[0]->getSelected();
    if(selected == nullptr) {
        return false; //failure: none selected
    }
    player->setMedia(QUrl::fromLocalFile(selected->url.c_str()));
    player->play();
    std::string log = "Started playing '" + selected->url + "'";
    qInfo(log.c_str());
    return true;
}

bool Engine::resumePlaying()
{
    if(player->state() != QMediaPlayer::PausedState) {
        return false; //failure: player wasn't in paused state.
    }
    player->play();
}

void Engine::pausePlaying()
{
    player->pause();
}

void Engine::stopPlaying()
{
    player->stop();
    delete player->playlist();
    player->setPlaylist(nullptr);
}

void Engine::playAll(Playlist * toPlayFrom)
{
    QMediaPlaylist * remaining = toPlayFrom->getRemaining();
    if(remaining != nullptr) {
        player->setPlaylist(remaining);
    }
}
