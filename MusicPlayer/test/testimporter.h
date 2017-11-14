#ifndef TESTSOMETHING_H
#define TESTSOMETHING_H

#include <QtTest/QtTest>
#include "song.h"

/**
 * @brief TestImporter --- for testing functionality of Importer class.
 * @author      Scott Wolfskill
 * @created     11/14/2017
 * @last_edit   11/14/2017
 */
class TestImporter : public QObject
{
    Q_OBJECT

private:
    std::string testFolder;
    Song * immediate; //song in immediate test Resources folder
    Song * sub1; //one song in Resources subdir
    Song * sub2; //2nd song ...

private slots:
    // functions executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    // functions executed by QtTest before and after each test
    /*void init();
    void cleanup();*/

    void testImportLibrary();
};


#endif // TESTSOMETHING_H
