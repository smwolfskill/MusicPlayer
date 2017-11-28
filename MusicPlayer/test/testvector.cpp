#include "testvector.h"

void TestVector::init()
{
    song1 = 10;
    song2 = 20;
    emptyPlaylist = new Vector<int>(0);
    song1Playlist = new Vector<int>(1);
}

void TestVector::cleanup()
{
    delete emptyPlaylist;
    delete song1Playlist;
}

/*void TestVector::testContains()
{
    emptyPlaylist->removeAt(0);
    //Test 1: empty
    QCOMPARE(emptyPlaylist->contains(song1), false);

    //Test 2: contains song1, not song2
    QCOMPARE(song1Playlist->contains(song1), true);
    QCOMPARE(song1Playlist->contains(song2), false);
}

void TestVector::testInsertAfter()
{
    //Add song2 to front of song1Playlist.
    song1Playlist->insertAfter(-1, song2);
}

void TestVector::testRemoveAt()
{
    //Test 1: invalid index
    QCOMPARE(song1Playlist->removeAt(1), false);

    //Test 2: remove 1st and only song
    QCOMPARE(song1Playlist->removeAt(0), true);
    QCOMPARE(song1Playlist->contains(song1), false);
}*/
