#include "testvector.h"

void TestVector::init()
{
    song1 = 10;
    song2 = 20;
    emptyPlaylist = new Vector<int>(0); //contains nothing
    song1Playlist = new Vector<int>(0); //contains song1
    song1Playlist->push_back(song1);
}

void TestVector::cleanup()
{
    delete emptyPlaylist;
    delete song1Playlist;
}

void TestVector::testContains()
{
    //Test 1: empty
    QCOMPARE(emptyPlaylist->contains(song1), false);

    //Test 2: contains song1, not song2
    QCOMPARE(song1Playlist->contains(song1), true);
    QCOMPARE(song1Playlist->contains(song2), false);
}

void TestVector::testFind()
{
    //Test 1: empty
    QCOMPARE(emptyPlaylist->find(song1), -1);

    //Test 2: song1 at beginning
    QCOMPARE(song1Playlist->find(song1), 0);

    //Test 3: song2 not found
    QCOMPARE(song1Playlist->find(song2), -1);
}

void TestVector::testInsertBefore()
{
    //Add song2 to front of song1Playlist.
    QCOMPARE(song1Playlist->insertBefore(0, song2), true);
    QVERIFY(song1Playlist->size() == 2);
    QCOMPARE((*song1Playlist)[0], song2); //song2 at front
    QCOMPARE((*song1Playlist)[1], song1); //song1 at back
}

void TestVector::testRemoveAt()
{
    //Test 1: invalid index
    QCOMPARE(song1Playlist->removeAt(1), false);

    //Test 2: remove 1st and only song
    QCOMPARE(song1Playlist->removeAt(0), true);
    QVERIFY(song1Playlist->size() == 0);
}

void TestVector::testSort()
{
    //qInfo("TODO");
    //QVERIFY(false);
}
