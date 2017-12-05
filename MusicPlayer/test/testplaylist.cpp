#include "testplaylist.h"

void TestPlaylist::init()
{
    song1 = new Song("url1", "title1", "artist1", "album1", "genre1", 2000);
    song2 = new Song("url2", "title2", "artist2", "album2", "genre2", 1900);
    emptyPlaylist = new Playlist("empty"); //empty playlist
    song1Playlist = new Playlist("song1");
    song1Playlist->songs.push_back(song1); //[song1]
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
