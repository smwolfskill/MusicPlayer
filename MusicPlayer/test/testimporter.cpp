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
    testFolder = "/home/scott/Qt/Projects/MusicPlayer/MusicPlayer/test/Resources/";
}

void TestImporter::testReadLines()
{
    using namespace std;
    const string testFile1 = testFolder + "readLineTest1.txt";
    const string testFile2 = testFolder + "readLineTest2.txt";
    //Test 0: basic: nullptr returned for file not found.
    Vector<string> * lines = Importer::readLines("aef.txt");
    QVERIFY(lines == nullptr);
    delete lines;

    /* Test 1: simple, 3 lines:
       line1
       line2
       end                      */
    lines = Importer::readLines(testFile1);
    string expected[] = {"line1", "line2", "end"};
    QVERIFY(lines != nullptr);
    QVERIFY(lines->size() == 3);
    for(unsigned i = 0; i < 3; i++) {
        QVERIFY(expected[i].compare((*lines)[i]) == 0);
    }

    delete lines;

    //Test 2: correct output (empty vector) for blank file
    lines = Importer::readLines(testFile2);
    QVERIFY(lines != nullptr);
    QVERIFY(lines->size() == 0);
    delete lines;
}

void TestImporter::testSaveLines()
{
    //Relies upon Importer::readLines working correctly.
    using namespace std;
    const string testFile1 = testFolder + "writeLineTest1.txt";
    Vector<string> lines(0);
    lines.push_back("start");
    lines.push_back("end");

    //Test 1: write to testFile1
    QCOMPARE(Importer::saveLines(testFile1, &lines), true);
    Vector<string> * writtenLines = Importer::readLines(testFile1);
    QVERIFY(writtenLines != nullptr);
    QVERIFY(*writtenLines == lines);
    delete writtenLines;
}

void TestImporter::testAppendLines()
{
    //Relies upon Importer::readLines working correctly.
    using namespace std;
    const string testFile2 = testFolder + "writeLineTest2.txt";
    Vector<string> lines(0);
    lines.push_back("writeLineTest2.txt"); //["filename", data ...] format
    Vector<string> * origLines = Importer::readLines(testFile2);

    //Test 1: append nothing to testFile1. Ensure the same as before.
    QCOMPARE(Importer::appendLines(testFile2, &lines, 1), true);
    Vector<string> * writtenLines = Importer::readLines(testFile2);
    QVERIFY(writtenLines != nullptr);
    QVERIFY(*writtenLines == *origLines);
    delete origLines;
    delete writtenLines;
}
