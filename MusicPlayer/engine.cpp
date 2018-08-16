#include "engine.h"
#include <QDir>
#include <QMediaPlaylist>
#include <stdlib.h>

const std::string Engine::EXEC_PATH = QDir::currentPath().toStdString();


std::string Engine::msToHMS(qint64 milliseconds)
{
    using namespace std;
    lldiv_t minsAndSecs = lldiv(milliseconds / 1000, 60L);
    qint64 seconds  = minsAndSecs.rem;
    lldiv_t hoursAndMins = lldiv(minsAndSecs.quot, 60);
    qint64 minutes  = hoursAndMins.rem;
    qint64 hours = hoursAndMins.quot;

    //Convert to string: "(H:)MM:SS" format
    string HMS = "";
    if(hours > 0) {
        HMS += to_string(hours) + ":";
    }
    if(minutes < 10) {
        HMS += "0";
    }
    HMS += to_string(minutes) + ":";
    if(seconds < 10) {
        HMS += "0";
    }
    HMS += to_string(seconds);
    return HMS;
}

Engine::Engine(const QObject * signalReceiver, const char * durationChangedSlot,
               const char * positionChangedSlot, const char * mediaChangedSlot, const char * mediaStatusChangedSlot)
{
    playlists = PlaylistVector(0);
    Playlist * sessionPlaylist = new Playlist("Now Playing"); //empty session playlist
    playlists.push_back(sessionPlaylist);
    metadata_path = EXEC_PATH + "/metadata/";
    player = new QMediaPlayer;
    metadata = nullptr;
    library = nullptr;
    loadedLibs = StringVector(0);
    repeatSong = false;
    repeatAll = false;

    QObject::connect(player, SIGNAL(durationChanged(qint64)), signalReceiver, durationChangedSlot);
    QObject::connect(player, SIGNAL(positionChanged(qint64)), signalReceiver, positionChangedSlot);
    QObject::connect(player, SIGNAL(currentMediaChanged(QMediaContent)), signalReceiver, mediaChangedSlot);
    QObject::connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), signalReceiver, mediaStatusChangedSlot);
}

Engine::Engine(std::string metadata_path) {
    //TODO: load playlists, incl. session playlist
    this->metadata_path = metadata_path;
    player = new QMediaPlayer;
    metadata = nullptr;
    library = nullptr;
    loadedLibs = StringVector(0);
    repeatSong = false;
    repeatAll = false;
}

Engine::~Engine() {
    //TODO: ensure save playlists, metadata on disk before this DTOR called
    playlists.clear();
    delete player;
    delete metadata;
    delete library;
}

StringVector * Engine::loadAll() {
    if(!loadMetadata()) {
        return nullptr; //no metadata exists, so nothing to load.
    }
    //1. Load all libraries specified in metadata libraryPaths.
    StringVector * messages = new StringVector(0);
    for(unsigned i = 1; i < metadata->libraryPaths->size(); i++) { //start after beginning ["filename", ..]
        messages->push_back( loadLibrary((*metadata->libraryPaths)[i]) );
    }
    //lib->sortLibrary(); //sort updated library
    return messages;
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

std::string Engine::addLibrary(const std::string directoryUrl)
{
    //1. Check if need to load metadata
    if(metadata == nullptr) {
        loadMetadata();
    }

    //2. Check if this library already in metadata (and implies already loaded)
    //nvm, allow user to have duplicate libraries in metadata. Will be skipped.
    /*if(metadata->libraryPaths->contains(directoryUrl)) {
        std::string msg = "Library '" + directoryUrl + "' already added to list.";
        qInfo(msg);
        return msg;
    }*/

    //3. Load library at directoryUrl
    metadata->libraryPaths->push_back(directoryUrl); //add to libraryPaths metadata
    std::string result = loadLibrary(directoryUrl);

    //4. Sort updated library: TODO
    //lib->sortLibrary();
    return result;
}

std::string Engine::loadLibrary(const std::string directoryUrl)
{
    if(library == nullptr) {
        library = new MusicLibrary();
    }
    if(loadedLibs.contains(directoryUrl)) { //already loaded
        std::string msg = "Skipping duplicate library '" + directoryUrl + "'";
        qInfo(msg.c_str());
        return msg;
    }
    loadedLibs.push_back(directoryUrl);
    return library->addToLibrary(directoryUrl);
}

void Engine::setVolume(int newVolume)
{
    //TODO: Make sure UI scale slider is logarithmic.
    player->setVolume(newVolume);
}

int Engine::pausedToggle()
{
    switch(player->state()) {
        case QMediaPlayer::PausedState:
            player->play();
            return 1;
            break;
        case QMediaPlayer::PlayingState:
            player->pause();
            return 0;
            break;
        default:
            return -1; //invalid request
    }
}

bool Engine::pause()
{
    bool validRequest = true;
    if(player->state() != QMediaPlayer::PlayingState) {
        validRequest = false;
    }
    player->pause();
    return validRequest;
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
    return true; //success
}

void Engine::playOnce(Song * toPlay)
{
    playlists[0]->songs.clear();
    playlists[0]->songs.push_back(toPlay);
    playlists[0]->goToFirst();
    playSelected();
}

void Engine::stopPlaying()
{
    player->stop();
    delete player->playlist();
    player->setPlaylist(nullptr);
}

void Engine::playAll(Playlist * toPlayFrom)
{
    SongVector remaining = toPlayFrom->getRemaining();
    if(remaining.size() > 0) {
        QMediaPlaylist * nowPlaying = Song::SongVectorToQMediaPlaylist(remaining);
        player->setPlaylist(nowPlaying);
        player->play();
        playlists[0]->songs.clear();
        playlists[0]->songs = remaining;
    }
}

void Engine::playAll(const SongVector * toPlayFrom, int selected_index)
{
    playlists[0]->songs.clear();
    playlists[0]->songs = *toPlayFrom;
    playlists[0]->goToIndex(selected_index);
    playSelected();
}

void Engine::playAtPosition(qint64 position)
{
    if(player->state() == QMediaPlayer::StoppedState) {
        playSelected();
    }
    player->play();
    player->setPosition(position);
}

void Engine::skip()
{
    playlists[0]->getNext();
    playSelected();
}

void Engine::rewind()
{
    playlists[0]->getPrevious();
    playSelected();
}

bool Engine::songFinished()
{
    if(repeatSong) {
        playSelected();
        return true;
    }
    if(playlists[0]->getNext(repeatAll) != nullptr) {
        //If at end of session playlist and repeatAll is true, will play beginning song
        playSelected();
        return true;
    }
    return false;
}
