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

    player = new QMediaPlayer;
    engine = new Engine(); //use default metadata path
    engine->loadAll(); //load metadata, then libraries it links to
    for(unsigned i = 0; i < engine->library->songs.size(); i++) {
        qInfo(engine->library->songs[i]->toString().c_str());
    }
}

FrmMain::~FrmMain()
{
    delete ui;
    delete engine;
    delete player;
    //qInfo("cleaned up frmMain.");
}

bool FrmMain::testReturn() {
    return true;
}

void FrmMain::on_btnPlay_clicked()
{
    using namespace std;
    /*QString path = "/home/scott/Desktop/ScotWolfskillPC/Music/1 - Hoist The Colours.mp3";
    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(50);
    player->play();
    qInfo("started playing file");*/

    //const char * path = "/home/scott/Desktop/ScotWolfskillPC/Music/1 - Hoist The Colours.mp3";
    /*const std::string path = "/home/scott/Desktop/ScotWolfskillPC/Music/Evoken";
    MusicLibrary * lib = Importer::importLibrary(path);
    delete lib;*/
}

void FrmMain::on_btnStop_clicked()
{
    player->stop();
    qInfo("stopped playing file");
}
