#include "testplaylist.h"

void TestPlaylist::init()
{
    song1 = new Song("url1", "title1", "artist1", "album1", "genre1", 2000);
    song2 = new Song("url2", "title2", "artist2", "album2", "genre2", 1900);
    SongVector withSong = SongVector(1);
    withSong.push_front(song1);
    emptyPlaylist = new Playlist("empty", SongVector(0), 0);
    song1Playlist = new Playlist("song1", withSong, 1);
}

void TestPlaylist::cleanup()
{
    delete emptyPlaylist;
    delete song1Playlist;
    delete song1;
    delete song2;
}

void TestPlaylist::testGoToSong()
{
    //Test 1: not found
    QCOMPARE(emptyPlaylist->goToSong(song1), false);

    //Test 2: found
    QCOMPARE(song1Playlist->goToSong(song1), true);
    QCOMPARE(song1Playlist->getSelected(), song1);
    QCOMPARE(song1Playlist->getSelected_index(), 0);
}

void TestPlaylist::testContainsSong()
{
    //Test 1: empty
    QCOMPARE(emptyPlaylist->containsSong(song1), false);

    //Test 2: contains song1, not song2
    QCOMPARE(song1Playlist->containsSong(song1), true);
    QCOMPARE(song1Playlist->containsSong(song2), false);
}

void TestPlaylist::testAddSong()
{
    emptyPlaylist->addSong(song1);
    QCOMPARE(emptyPlaylist->containsSong(song1), true);
}

void TestPlaylist::testAddSongAfter()
{
    //Add song2 to front of song1Playlist.
    song1Playlist->addSongAfter(-1, song2);
    song1Playlist->goToFirst();
    QCOMPARE(song1Playlist->getSelected(), song2); //1st element is song1
    QCOMPARE(song1Playlist->getNext(), song1); //2nd element is song2
    QCOMPARE(song1Playlist->getSelected_index(), 1);
}

void TestPlaylist::testRemoveSongAt()
{
    //Test 1: invalid index
    QCOMPARE(song1Playlist->removeSongAt(1), false);

    //Test 2: remove 1st and only song
    QCOMPARE(song1Playlist->removeSongAt(0), true);
    QCOMPARE(song1Playlist->containsSong(song1), false);
    QCOMPARE(song1Playlist->getSelected(), nullptr);
}
