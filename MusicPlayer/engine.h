#ifndef ENGINE_H
#define ENGINE_H

#include "musiclibrary.h"
#include "metadata.h"
#include "playlist.h"
#include <string>
#include <QMediaPlayer>

/**
 * @brief Engine --- Core functionality of the Music Player, handling loading/saving,
 *                   song locating and playing.
 * @author      Scott Wolfskill
 * @created     12/04/2017
 * @last_edit   12/05/2017
 */
class Engine
{
public:
    //Vars:
    static const std::string EXEC_PATH; //path of this running executable program

    std::string metadata_path; //path of metadata location
    Metadata * metadata;
    MusicLibrary * library;
    PlaylistVector playlists; //[session playlist, user_created1, user_created2, ...] format

    //Methods:
    Engine();
    Engine(std::string metadata_path);
    ~Engine();

    //Saving/Loading:
    bool loadAll();
    bool loadMetadata();
    bool saveMetadata();

    /**
     * @brief Add and load a new library to the engine if not already loaded.
     * @param directoryUrl Absolute path of library.
     * @return false if already loaded.
     */
    bool addLibrary(const std::string directoryUrl);

    /**
     * @brief Load a library into the engine, appending onto lib.
     * @param directoryUrl Absolute path of library.
     * @return false if directory not found.
     */
    bool loadLibrary(const std::string directoryUrl);

    //Playing features:

    /**
     * @brief Set volume of the player.
     * @param newVolume
     */
    void setVolume(int newVolume);

    /**
     * @brief Play currently selected song in session playlist playlists[0].
     * @return false if none selected or currently selected Song unable to be played.
     */
    bool playSelected();
    bool resumePlaying();
    void pausePlaying();
    void stopPlaying();

    /**
     * @brief Plays the remainder of a Playlist from its selected Song until the end.
     *        If none selected, starts at beginning.
     * @param toPlayFrom Playlist to play.
     */
    void playAll(Playlist * toPlayFrom);

private:
    QMediaPlayer * player;
};

#endif // ENGINE_H
