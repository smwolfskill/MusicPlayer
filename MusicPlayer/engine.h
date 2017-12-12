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
 * @last_edit   12/11/2017
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
    /**
     * @brief Convert milliseconds to string format H:MM:SS. Typically expect M:SS.
     * @param milliseconds
     * @return string representation of time.
     */
    static std::string msToHMS(qint64 milliseconds);

    Engine(const QObject * signalReceiver, const char * durationChangedSlot, const char * positionChangedSlot);
    Engine(std::string metadata_path);
    ~Engine();

    //Saving/Loading:
    /**
     * @brief Loads metadata and all libraries listed into the engine.
     * @return Nullptr if no metadata exists, else array of error messages encountered when loading library.
     *         An entry of "" indicates success for that library. Caller MUST deallocate.
     */
    StringVector * loadAll();

    bool loadMetadata();
    bool saveMetadata();

    /**
     * @brief Add and load a new library to the engine (and metadata) if not already present.
     * @param directoryUrl Absolute path of library.
     * @return result of loadLibrary.
     */
    std::string addLibrary(const std::string directoryUrl);

    /**
     * @brief Load a library into the engine, appending onto lib.
     * @param directoryUrl Absolute path of library.
     * @return "" if success; else error message.
     */
    std::string loadLibrary(const std::string directoryUrl);

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

    //TODO: add method to play a single song, which sets the session playlist to that and calls playSelected().

    /**
     * @brief Pause or resume currently playing media, if any.
     * @return 1 if was paused, now playing; 0 if was playing, now paused; -1 if invalid request (no playing media).
     */
    int pausedToggle();

    /**
     * @brief Definitively pause the currently playing media.
     * @return false if no media is playing.
     */
    bool pause();

    void stopPlaying();

    /**
     * @brief Plays the remainder of a Playlist from its selected Song until the end.
     *        If none selected, starts at beginning.
     * @param toPlayFrom Playlist to play.
     */
    void playAll(Playlist * toPlayFrom);

    void playAtPosition(qint64 position);

private:
    StringVector loadedLibs; //list of libraries already loaded into the engine
    QMediaPlayer * player;
};

#endif // ENGINE_H
