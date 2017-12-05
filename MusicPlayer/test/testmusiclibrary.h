#ifndef TESTMUSICLIBRARY_H
#define TESTMUSICLIBRARY_H


#include <QtTest/QtTest>
#include "musiclibrary.h"

/**
 * @brief TestMusicLibrary --- for testing functionality of MusicLibrary class.
 * @author      Scott Wolfskill
 * @created     12/04/2017
 * @last_edit   12/04/2017
 */
class TestMusicLibrary : public QObject
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

    void testAddToLibrary();
};

#endif // TESTMUSICLIBRARY_H
