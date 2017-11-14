#include <QtTest>
#include <QApplication>
#include "testimporter.h"
#include "testsong.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    int status = 0;
    if(true) //run Importer class tests
       {
          TestImporter tc;
          status |= QTest::qExec(&tc, argc, argv);
       }
    if(true) //run Song class tests
       {
          TestSong tc;
          status |= QTest::qExec(&tc, argc, argv);
       }
    return status;
}
