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

    engine = new Engine(); //use default metadata path
    engine->loadAll(); //load metadata, then libraries it links to
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
}

FrmMain::~FrmMain()
{
    delete ui;
    delete engine;
    //qInfo("cleaned up frmMain.");
}

bool FrmMain::testReturn() {
    return true;
}

void FrmMain::on_btnPlay_clicked()
{
    if(!engine->playSelected()) {
        qWarning("Failed to play selected!");
    }
}

void FrmMain::on_btnStop_clicked()
{
    engine->stopPlaying();
}
