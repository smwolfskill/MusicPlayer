#include "testvector.h"

void TestVector::init()
{
    song1 = 10;
    song2 = 20;
    song3 = 30;
    emptyPlaylist = new Vector<int>(0); //contains nothing
    song1Playlist = new Vector<int>(0); //contains song1
    song1Playlist->push_back(song1);
    playlist2 = new Vector<int>(0);
    playlist2->push_back(song1);
    playlist2->push_back(song2);
    playlist2->push_back(song3);
}

void TestVector::cleanup()
{
    delete emptyPlaylist;
    delete song1Playlist;
    delete playlist2;
}

void TestVector::testContains()
{
    //Test 1: empty
    QCOMPARE(emptyPlaylist->contains(song1), false);

    //Test 2: contains song1, not song2 or song3
    QCOMPARE(song1Playlist->contains(song1), true);
    QCOMPARE(song1Playlist->contains(song2), false);
    QCOMPARE(song1Playlist->contains(song3), false);
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
    QVERIFY(song1Playlist->size() == 1);

    //Add song2 to front of song1Playlist.
    QCOMPARE(song1Playlist->insertBefore(0, song2), true);
    QVERIFY(song1Playlist->size() == 2);
    QCOMPARE((*song1Playlist)[0], song2); //song2 at front
    QCOMPARE((*song1Playlist)[1], song1); //song1 at back

    //Add song3 to middle of song1Playlist after song2 and before song1.
    QCOMPARE(song1Playlist->insertBefore(1, song3), true);
    QVERIFY(song1Playlist->size() == 3);
    QCOMPARE((*song1Playlist)[0], song2); //song2 at front
    QCOMPARE((*song1Playlist)[1], song3); //song3 in middle
    QCOMPARE((*song1Playlist)[2], song1); //song1 at back
}

void TestVector::testRemoveAt()
{
    //Test 1: invalid index
    QCOMPARE(song1Playlist->removeAt(1), false);

    //Test 2: remove 1st and only song
    QVERIFY(song1Playlist->size() == 1);
    QCOMPARE(song1Playlist->removeAt(0), true);
    QVERIFY(song1Playlist->size() == 0);

    //Test 3: remove middle song in 3-length vector
    QVERIFY(playlist2->size() == 3);
    QCOMPARE(playlist2->removeAt(1), true);
    QVERIFY(playlist2->size() == 2);
    QCOMPARE((*playlist2)[0], song1); //song1 at front
    QCOMPARE((*playlist2)[1], song3); //song3 at back
}

void TestVector::testSort()
{
    //playlist2 should start in ascending order and finish in descending:
    playlist2->sort(compareDescending);
    QCOMPARE((*playlist2)[0], song3); //song3 (greatest) moved to front
    QCOMPARE((*playlist2)[1], song2); //song2 remains in middle
    QCOMPARE((*playlist2)[2], song1); //song1 (least) moved to back
}

bool TestVector::compareDescending(int a, int b)
{
    return a > b;
}
