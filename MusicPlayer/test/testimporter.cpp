#include "testimporter.h"
#include "importer.h"
#include "musiclibrary.h"
#include <unistd.h>


void TestImporter::initTestCase()
{
    //TODO: Change to "(localDir)/test/Resources"
    /*char temp[PATH_MAX];
    std::string curPath = getcwd(temp, PATH_MAX) ? std::string( temp ) : std::string("");
    //This is in the build directory  =/
    qInfo(curPath.c_str());*/
    //qInfo(std::experimental::filesystem::current_path().c_str());

    testFolder = "/home/scott/Qt/Projects/MusicPlayer/MusicPlayer/test/Resources";
    //Expected Songs:
    immediate = new Song(testFolder + "/Lostprophets - Can't Catch Tomorrow.mp3", "Can't Catch Tomorrow",
                         "Lostprophets", "Liberation Transmission", "Rock", 2006);
    std::string subDir = testFolder + "/Music Folder 1";
    sub1 = new Song(subDir + "/Coldplay - Fix You.mp3", "Fix You", "Coldplay", "X&Y", "Alternative", 2005);
    sub2 = new Song(subDir + "/Coldplay - Talk.mp3", "Talk", "Coldplay", "X&Y", "Alternative", 2005);
}

void TestImporter::cleanupTestCase()
{
    delete immediate;
    delete sub1;
    delete sub2;
}

void TestImporter::testImportLibrary() {
    //QCOMPARE(testFolder.c_str(), "/home/scott/Qt/Projects/MusicPlayer/test/Resources");
    MusicLibrary * testLib = Importer::importLibrary(testFolder);

    //Test 1: not null
    QVERIFY(testLib != nullptr);

    //Test 2: Simple: correctly parsed song in immediate folder
    Song * parsedImmediate = testLib->getSong(immediate->title);
    QVERIFY(parsedImmediate != nullptr);
    QCOMPARE(immediate->Equals(parsedImmediate), true);

    //Test 3: Recursive + multi files: correctly parsed 2 songs in subdir
    Song * parsedSub1 = testLib->getSong(sub1->title);
    QVERIFY(parsedSub1 != nullptr);
    QCOMPARE(sub1->Equals(parsedSub1), true);

    Song * parsedSub2 = testLib->getSong(sub2->title);
    QVERIFY(parsedSub2 != nullptr);
    QCOMPARE(sub2->Equals(parsedSub2), true);

    //cleanup
    delete testLib;
}
