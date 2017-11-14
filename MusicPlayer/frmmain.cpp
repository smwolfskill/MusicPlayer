#include "frmmain.h"
#include "ui_frmmain.h"
#include "importer.h"
#include "musiclibrary.h"

FrmMain::FrmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);

    player = new QMediaPlayer;
}

FrmMain::~FrmMain()
{
    delete ui;
    delete player;
    //qInfo("cleaned up frmMain.");
}

bool FrmMain::testReturn() {
    return true;
}

void FrmMain::on_btnPlay_clicked()
{
    /*QString path = "/home/scott/Desktop/ScotWolfskillPC/Music/1 - Hoist The Colours.mp3";
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(50);
    player->play();
    qInfo("started playing file");*/

    //const char * path = "/home/scott/Desktop/ScotWolfskillPC/Music/1 - Hoist The Colours.mp3";
    const std::string path = "/home/scott/Desktop/ScotWolfskillPC/Music/Evoken";
    MusicLibrary * lib = Importer::importLibrary(path);
    delete lib;
}

void FrmMain::on_btnStop_clicked()
{
    player->stop();
    qInfo("stopped playing file");
}
