#include "frmmain.h"
#include "ui_frmmain.h"
#include "importer.h"
#include "musiclibrary.h"
#include "vector.h"


FrmMain::FrmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    viewingData = nullptr;
    viewingSongs = nullptr;
    smallFont = "<font size=\"2\">";
    iconPause = ui->actionPause->icon();
    iconResume = ui->actionPlay->icon();
    setState_noneSelected();

    //Init. context menus:
    playlistMenu = new PlaylistMenu(this, SLOT(ctxAction_renamePlaylist()), SLOT(ctxAction_copyPlaylist()), SLOT(ctxAction_newPlaylist()));
    songMenu = new SongMenu(this, SLOT(ctxAction_playOnce()), SLOT(ctxAction_playNext()),
                                SLOT(ctxAction_playLast()), SLOT(ctxAction_playAll()),
                                SLOT(ctxAction_addToPlaylist()));
    playlistItemMenu = new PlaylistItemMenu(this, SLOT(ctxAction_playOnce()), SLOT(ctxAction_playNext()),
                                SLOT(ctxAction_playLast()), SLOT(ctxAction_playAll()),
                                SLOT(ctxAction_addToPlaylist()), SLOT(ctxAction_RemoveFromPlaylist()));

    /*sliVolume = new QSlider(ui->mainToolBar);
    sliVolume->setMinimum(0);
    sliVolume->setMaximum(100);
    sliVolume->setValue(23);
    sliVolume->setOrientation(ui->mainToolBar->orientation());*/
    updateVolumeTooltip();
    sliVolume_action = new QWidgetAction(ui->mainToolBar);
    sliVolume_action->setDefaultWidget(ui->sliVolume);
    //sliPlayback_action = new QWidgetAction(ui->mainToolBar);
    //sliPlayback_action->setDefaultWidget(ui->sliPlayback);
    ui->mainToolBar->addAction(sliVolume_action/*, this, SLOT()*/);
    ui->mainToolBar->addSeparator();
    //ui->mainToolBar->addAction(sliPlayback_action);
    //ui->actionPause->triggered
    //connect(ui->actionPlay, QAction::Trigger, this, SLOT(hi));
    connect(ui->actionPlay, SIGNAL(triggered(bool)), this, SLOT(on_media_play()));
    connect(ui->actionStop, SIGNAL(triggered(bool)), this, SLOT(on_media_stop()));
    connect(ui->actionPause, SIGNAL(triggered(bool)), this, SLOT(on_media_pause()));
    connect(ui->actionSkip, SIGNAL(triggered(bool)), this, SLOT(on_media_skip()));
    connect(ui->actionRewind, SIGNAL(triggered(bool)), this, SLOT(on_media_rewind()));
    connect(ui->lstCategories, SIGNAL(currentRowChanged(int)), this, SLOT(on_select_lstCategory(int)));
    connect(ui->lstCategoryMembers, SIGNAL(currentRowChanged(int)), this, SLOT(on_select_lstCategoryMember(int)));
    connect(ui->lstCategories, SIGNAL(currentRowChanged(int)), this, SLOT(on_select_tblSongs(int)));

    //Raise Context menus:
    connect(ui->lstCategoryMembers, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ctxMenu_lstCategoryMembers(QPoint)));
    connect(ui->lstCurrentPlaylist, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ctxMenu_lstCurrentPlaylist(QPoint)));
    connect(ui->tblSongs, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ctxMenu_tblSongs(QPoint)));


    //Load engine
    ui->statusBar->showMessage("Loading libraries...");
    engine = new Engine(this, SLOT(on_media_durationChanged(qint64)), SLOT(on_media_positionChanged(qint64))); //use default metadata path
    StringVector * messages = engine->loadAll(); //load metadata, then libraries it links to
    if(messages != nullptr) {
        for(unsigned i = 0; i < messages->size(); i++) {
            ui->statusBar->showMessage((*messages)[i].c_str());
        }
    } else { //no metadata
        ui->statusBar->showMessage("No libraries loaded (add one in settings...)");
    }
    delete messages;

    setState_songSelected();

    //Show library song contents
    qInfo("Library contents:");
    for(unsigned i = 0; i < engine->library->songs.size(); i++) {
        qInfo(engine->library->songs[i]->toString().c_str());
    }
    qInfo("======");
    //Temp: make session playlist 1st song in library
    Playlist * sessionPlaylist = engine->playlists[0];
    sessionPlaylist->songs.push_back(engine->library->songs[0]);
    qInfo("Session playlist:");
    for(unsigned i = 0; i < sessionPlaylist->songs.size(); i++) {
        qInfo(sessionPlaylist->songs[i]->toString().c_str());
    }
    qInfo("======");
    //

    //Set Playlists view as default, and update Now Playing
    ui->lstCategories->setCurrentRow(0);
    showNowPlaying();
}

FrmMain::~FrmMain()
{
    delete ui;
    delete sliVolume_action;
    delete engine;
    delete playlistMenu;
    delete songMenu;
    delete playlistItemMenu;
    //qInfo("cleaned up frmMain.");
}

void FrmMain::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    //TODO:Resize stuff if needed
}

void FrmMain::on_sliVolume_valueChanged(int value)
{
    engine->setVolume(value);
    updateVolumeTooltip();
}

void FrmMain::updateVolumeTooltip() {
    std::string ttText = "Volume (" + std::to_string(ui->sliVolume->value()) + ")";
    ui->sliVolume->setToolTip(ttText.c_str());
}

void FrmMain::updateLblPlayback()
{
    std::string playbackText = songPosition + "/" + songDuration;
    ui->lblPlaybackTime->setText(playbackText.c_str());
}

void FrmMain::showNowPlaying()
{
    SongVector * nowPlaying = &engine->playlists[0]->songs;
    ui->lstCurrentPlaylist->clear();
    for(unsigned i = 0; i < nowPlaying->size(); i++) {
        ui->lstCurrentPlaylist->addItem(tr((*nowPlaying)[i]->title.c_str()));
    }
}

void FrmMain::showPlaylists(const PlaylistVector &playlists)
{
    viewingMode = PLAYLISTS;
    viewingData = (void*) &playlists;
    for(unsigned i = 0; i < playlists.size(); i++) {
        ui->lstCategoryMembers->addItem(tr(playlists[i]->getName().c_str()));
    }
}

void FrmMain::showArtists(const ArtistVector &artists)
{
    viewingMode = ARTISTS;
    viewingData = (void*) &artists;
    for(unsigned i = 0; i < artists.size(); i++) {
        ui->lstCategoryMembers->addItem(tr(artists[i]->name.c_str()));
    }
}

void FrmMain::showAlbums(const AlbumVector &albums)
{
    viewingMode = ALBUMS;
    viewingData = (void*) &albums;
    for(unsigned i = 0; i < albums.size(); i++) {
        ui->lstCategoryMembers->addItem(tr(albums[i]->name.c_str()));
    }
}

void FrmMain::showGenres(const GenreVector &genres)
{
    viewingMode = GENRES;
    viewingData = (void*) &genres;
    for(unsigned i = 0; i < genres.size(); i++) {
        ui->lstCategoryMembers->addItem(tr(genres[i]->name.c_str()));
    }
}

void FrmMain::showSongs(const SongVector &songs)
{
    viewingSongs = &songs;
    for(unsigned i = 0; i < songs.size(); i++) {
        if(i >= ui->tblSongs->rowCount()) { //insert new rows if needed
            ui->tblSongs->insertRow(i);
        }
        ui->tblSongs->setItem(i, 0, new QTableWidgetItem(tr(songs[i]->title.c_str())));
        ui->tblSongs->setItem(i, 1, new QTableWidgetItem(tr(songs[i]->artist.c_str())));
        ui->tblSongs->setItem(i, 2, new QTableWidgetItem(tr(songs[i]->album.c_str())));
        ui->tblSongs->setItem(i, 3, new QTableWidgetItem(tr(std::to_string(songs[i]->trackNum).c_str())));
        ui->tblSongs->setItem(i, 4, new QTableWidgetItem(tr(std::to_string(songs[i]->year).c_str())));
        ui->tblSongs->setItem(i, 5, new QTableWidgetItem(tr(songs[i]->genre.c_str())));
    }
}

void FrmMain::on_media_play()
{
    qint64 songLength = engine->playSelected();
    if(songLength == -1L) {
        qWarning("Failed to play selected!");
    }
    setState_playing();
}

void FrmMain::on_media_stop()
{
    engine->stopPlaying();
    setState_songSelected();
}

void FrmMain::on_media_pause()
{
    switch(engine->pausedToggle()) {
        case 1: //was paused, now playing
            qInfo("resume playing");
            setState_playing();
            break;
        case 0: //was playing, now paused
            qInfo("pause");
            setState_paused();
            break;
        default:
            qInfo("invalid pause request");
            ui->statusBar->showMessage("Cannot pause/resume; no media is playing.", 5000); //show for 5 seconds
    }
}

void FrmMain::on_media_skip()
{

}

void FrmMain::on_media_rewind()
{

}

void FrmMain::on_media_durationChanged(qint64 newDuration)
{
    //qInfo("duration set!");
    songDuration = Engine::msToHMS(newDuration);
    updateLblPlayback();
    ui->sliPlayback->setMinimum(0);
    ui->sliPlayback->setMaximum(newDuration);
    ui->sliPlayback->setTickInterval(newDuration / 4); //mark quarters
}

void FrmMain::on_media_positionChanged(qint64 newPosition)
{
    songPosition = Engine::msToHMS(newPosition);
    updateLblPlayback();
    ui->sliPlayback->setValue(newPosition);
}

void FrmMain::on_select_lstCategory(int index)
{
    QListWidgetItem * selected = ui->lstCategories->currentItem();
    //qInfo(selected->text().toStdString().c_str());
    ui->lstCategoryMembers->clear();
    ui->tblSongs->clearContents();
    if(selected->text() == "Playlists") {
        showPlaylists(engine->playlists);
    } else if(selected->text() == "Artists") {
        showArtists(engine->library->artists);
    } else if(selected->text() == "Albums") {
        showAlbums(engine->library->albums);
    } else if(selected->text() == "Genres") {
        showGenres(engine->library->genres);
    } else if(selected->text() == "Songs") {
        showSongs(engine->library->songs);
    }
}

void FrmMain::on_select_lstCategoryMember(int index)
{
    if(index >= 0) {
        //index corresponds to viewingData, which is a type of vector
        switch(viewingMode) {
        case PLAYLISTS: { //1 playlist selected. show songs.
            ui->tblSongs->clearContents();
            PlaylistVector * displayed = (PlaylistVector*) viewingData;
            showSongs((*displayed)[index]->songs);
            break;
        } case ARTISTS: { //1 artist selected. show his albums.
            ui->lstCategoryMembers->clear();
            ArtistVector * displayed = (ArtistVector*) viewingData;
            showAlbums((*displayed)[index]->albums);
            break;
        } case ALBUMS: { //1 album selected. show its songs.
            ui->tblSongs->clearContents();
            AlbumVector * displayed = (AlbumVector*) viewingData;
            showSongs((*displayed)[index]->songs);
            break;
        } case GENRES: {//1 genre selected. show its songs.
            ui->tblSongs->clearContents();
            GenreVector * displayed = (GenreVector*) viewingData;
            showSongs((*displayed)[index]->songs);
            break;
        }
        }
    }
}

void FrmMain::on_select_tblSongs(int index)
{
    //update selected lbl if not playing

}

void FrmMain::setState_noneSelected()
{
    ui->actionSkip->setEnabled(false);
    ui->actionRewind->setEnabled(false);
    ui->actionPlay->setEnabled(false);
    ui->actionStop->setEnabled(false);
    ui->actionPause->setEnabled(false);
    ui->actionPause->setIcon(iconPause);
    ui->actionPause->setToolTip("Pause");
    ui->lblPlaybackStatus->setText((smallFont + "None selected.</font>").c_str());
}

void FrmMain::setState_songSelected()
{
    ui->actionSkip->setEnabled(true);
    ui->actionRewind->setEnabled(true);
    ui->actionPlay->setEnabled(true);
    ui->actionStop->setEnabled(false);
    ui->actionPause->setEnabled(false);
    ui->actionPause->setIcon(iconPause);
    ui->actionPause->setToolTip("Pause");
    ui->lblPlaybackStatus->setText((smallFont + "Selected</font>").c_str());
}

void FrmMain::setState_playing()
{
    ui->actionPlay->setEnabled(false);
    ui->actionPause->setEnabled(true);
    ui->actionStop->setEnabled(true);
    ui->actionPause->setIcon(iconPause);
    ui->actionPause->setToolTip("Play");
    ui->lblPlaybackStatus->setText((smallFont + "Playing</font>").c_str());
}

void FrmMain::setState_paused()
{
    ui->actionPause->setIcon(iconResume);
    ui->actionPause->setToolTip("Resume");
    ui->lblPlaybackStatus->setText((smallFont + "Paused</font>").c_str());
}

void FrmMain::on_sliPlayback_sliderReleased()
{
    engine->playAtPosition(ui->sliPlayback->value());
    //engine->pausedToggle(); //unpause at new position
    setState_playing();
}

void FrmMain::on_sliPlayback_sliderPressed()
{
    //pause while selecting new position
    if(!engine->pause()) {
        //engine wasn't playing anything. Start playing for correct bookkeeping, then pause.
        engine->playSelected();
        engine->pause();
    }
}

void FrmMain::ctxMenu_lstCategoryMembers(const QPoint &pos)
{
    if(viewingMode == PLAYLISTS) { //only display Playlist menu if "Playlists" is selected in lstCategories
        playlistMenu->exec(ui->lstCategoryMembers->mapToGlobal(pos));
    }
}

//Context menu raise events:
void FrmMain::ctxMenu_lstCurrentPlaylist(const QPoint &pos)
{
    playlistItemMenu->exec(ui->lstCurrentPlaylist->mapToGlobal(pos));
}

void FrmMain::ctxMenu_tblSongs(const QPoint &pos)
{
    if(viewingMode == PLAYLISTS) { //show playlist item menu; "Playlists" is selected
        playlistItemMenu->exec(ui->tblSongs->mapToGlobal(pos));
    } else { //show normal song menu
        songMenu->exec(ui->tblSongs->mapToGlobal(pos));
    }
}

//Context menu action events:
void FrmMain::ctxAction_playOnce()
{
    //TODO: some way to get current song to do something with
    //qInfo(ui->lstCurrentPlaylist->currentItem()->text().toStdString().c_str());
}

void FrmMain::ctxAction_playNext()
{

}

void FrmMain::ctxAction_playLast()
{

}

void FrmMain::ctxAction_playAll()
{

}

void FrmMain::ctxAction_addToPlaylist()
{

}

void FrmMain::ctxAction_RemoveFromPlaylist()
{

}

void FrmMain::ctxAction_renamePlaylist()
{

}

void FrmMain::ctxAction_copyPlaylist()
{
    //TODO: show dialog window for copy name
}

void FrmMain::ctxAction_newPlaylist()
{
    //TODO: show dialog window for name
}
