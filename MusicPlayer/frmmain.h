#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QWidgetAction>
#include <QSlider>
#include <QListWidgetItem>
#include "engine.h"
#include "playlistmenu.h"
#include "songmenu.h"
#include "playlistitemmenu.h"
#include "playlist.h"

/**
 * @brief FrmMain --- 'View' component of Music Player. Holds engine and main GUI elements and events.
 * @author      Scott Wolfskill
 * @created     11/13/2017
 * @last_edit   12/12/2017
 */
namespace Ui {
class FrmMain;
}

class FrmMain : public QMainWindow
{
    Q_OBJECT

public:
    //Vars:
    Engine * engine;

    //Methods:
    explicit FrmMain(QWidget *parent = 0);
    ~FrmMain();

private slots:
    //void resizeEvent(QResizeEvent * event);

    void on_sliVolume_valueChanged(int value);

    //Playback slots:
    void on_media_play();
    void on_media_stop();
    void on_media_pause();
    void on_media_skip();
    void on_media_rewind();
    void on_media_durationChanged(qint64 newDuration); //called when length of song playing is set
    void on_media_positionChanged(qint64 newPosition); //called when current position in song playing is updated

    void on_select_lstCategory(int index);
    void on_select_lstCategoryMember(int index);
    void on_select_tblSongs(int rowIndex, int colIndex, int oldRow, int oldCol);
    void on_select_lstCurrentPlaylist(int index);

    void on_sliPlayback_sliderReleased();
    void on_sliPlayback_sliderPressed();

    //Context menu raise events:
    void ctxMenu_lstCategoryMembers(const QPoint &pos);
    void ctxMenu_lstCurrentPlaylist(const QPoint &pos);
    void ctxMenu_tblSongs(const QPoint &pos);

    //Context menu action events:
    void ctxAction_playOnce();
    void ctxAction_playNext();
    void ctxAction_playLast();
    void ctxAction_playAll();
    void ctxAction_addToPlaylist();
    void ctxAction_RemoveFromPlaylist();
    void ctxAction_renamePlaylist();
    void ctxAction_copyPlaylist();
    void ctxAction_newPlaylist();


private:
    //Vars:
    Ui::FrmMain *ui;
    QWidgetAction * sliVolume_action;
    std::string songDuration; //display length of song playing (e.g. "12:03")
    std::string songPosition; //display current position in song playing (e.g. "0:05")
    std::string smallFont; //will contain HTML beginning markup for a small text font
    QIcon iconPause; //icon to display on actionPause when can pause current song
    QIcon iconResume; //icon to display on actionPause when current song is paused and can
    bool nonePlaying;

    void * viewingData; //using VIEW, will be typecast into appropriate (type)Vector *
    const SongVector * tblSongs_contents; //ptr. to songs currently displayed to user in tblSongs
    const SongVector * lstCurrentPlaylist_contents; //ptr. to songs currently displaying in lstCurrentPlaylist_contents
    const SongVector * selectedSongList; //ptr. to songs in list user is currently selecting. Either tblSongs_contents or lstCurrentPlaylist_contents.
    int selectedIndex; //index in selectedSongList of currently selected song.
    //Song * selected; //current Song selected
    enum VIEW {PLAYLISTS, ARTISTS, ALBUMS, GENRES}; //represents what kind of data is displayed to user
    VIEW viewingMode;

    //Context menus:
    PlaylistMenu * playlistMenu;
    SongMenu * songMenu; //context menu for song actions
    PlaylistItemMenu * playlistItemMenu; //context menu for playlist item actions

    //Methods:
    void setState_noneSelected();
    void setState_songSelected();
    void setState_playing();
    void setState_paused();
    void updateVolumeTooltip();
    void updateLblPlayback();

    void showNowPlaying();
    void showPlaylists(const PlaylistVector &playlists);
    void showArtists(const ArtistVector &artists);
    void showAlbums(const AlbumVector &albums);
    void showGenres(const GenreVector &genres);
    void showSongs(const SongVector &songs);
};

#endif // FRMMAIN_H
