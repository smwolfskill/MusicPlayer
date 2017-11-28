#ifndef TESTPLAYLIST_H
#define TESTPLAYLIST_H

#include <QtTest/QtTest>
#include "playlist.h"

/**
 * @brief TestPlaylist --- for testing functionality of Playlist class.
 * @author      Scott Wolfskill
 * @created     11/27/2017
 * @last_edit   11/27/2017
 */
class TestPlaylist : public QObject
{
    Q_OBJECT

private:
    Playlist * emptyPlaylist;
    Playlist * song1Playlist;
    Song * song1;
    Song * song2;
    SongVector withSong;

private slots:
    // functions executed by QtTest before and after test suite
    /*void initTestCase();
    void cleanupTestCase();*/

    // functions executed by QtTest before and after each test
    void init();
    void cleanup();

    void testGoToSong();
    void testContainsSong();
    void testAddSong();
    void testAddSongAfter();
    void testRemoveSongAt();
};

#endif // TESTPLAYLIST_H
