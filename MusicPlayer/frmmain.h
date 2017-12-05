#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "engine.h"

namespace Ui {
class FrmMain;
}

class FrmMain : public QMainWindow
{
    Q_OBJECT

public:
    //Vars:
    Engine * engine;
    QMediaPlayer * player;

    //Methods:
    explicit FrmMain(QWidget *parent = 0);
    ~FrmMain();
    bool testReturn(); //DELETE ONCE REAL CODING

private slots:
    void on_btnPlay_clicked();
    void on_btnStop_clicked();

private:
    Ui::FrmMain *ui;
};

#endif // FRMMAIN_H
