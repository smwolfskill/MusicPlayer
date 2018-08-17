#include "testsong.h"
#include "song.h"


void TestSong::testEquals()
{
    Song a("url", "2", "3", "4", "5", 1, 1995);
    Song b("url", "2", "3", "4", "5", 1, 1995);
    Song c("url", "2", "0", "4", "5", 1, 1995);
    //Test 1: assert reflexive + correct result when actually equal
    QCOMPARE(a.Equals(&b), true);
    QCOMPARE(b.Equals(&a), true);

    //Test 2: assert reflexive + correct result when actually unequal
    QCOMPARE(b.Equals(&c), false);
    QCOMPARE(c.Equals(&b), false);
}

void TestSong::testCompareBy_title()
{
    Song a("url", "a", "3", "4", "5", 1, 1995);
    Song b("url", "az", "3", "4", "5", 1, 1995);
    Song c("url", "a", "0", "4", "5", 1, 1995);

    //Test 1: a alphabetically before b
    QCOMPARE(Song::compareBy_title(&a, &b), true); //a.title is before b.title
    QCOMPARE(Song::compareBy_title(&b, &a), false); //check reflexive

    //Test 2: equality => false
    QCOMPARE(Song::compareBy_title(&a, &c), false); //return false for equality
    QCOMPARE(Song::compareBy_title(&c, &a), false); //reflexive
}

void TestSong::testCompareBy_artist()
{
    Song a("url", "2", "artist", "4", "5", 1, 1995);
    Song b("url", "2", "different", "4", "5", 1, 1995);
    Song c("url", "2", "artist", "4", "5", 1, 1995);

    //Test 1: a alphabetically before b
    QCOMPARE(Song::compareBy_artist(&a, &b), true); //a.artist is before b.artist
    QCOMPARE(Song::compareBy_artist(&b, &a), false); //check reflexive

    //Test 2: equality => false
    QCOMPARE(Song::compareBy_artist(&a, &c), false); //return false for equality
    QCOMPARE(Song::compareBy_artist(&c, &a), false); //reflexive
}

void TestSong::testCompareBy_album()
{
    Song a("url", "2", "3", "album", "5", 1, 1995);
    Song b("url", "2", "3", "anew album", "5", 1, 1995);
    Song c("url", "2", "3", "album", "5", 1, 1995);

    //Test 1: a alphabetically before b
    QCOMPARE(Song::compareBy_album(&a, &b), true); //a.album is before b.album
    QCOMPARE(Song::compareBy_album(&b, &a), false); //check reflexive

    //Test 2: equality => false
    QCOMPARE(Song::compareBy_album(&a, &c), false); //return false for equality
    QCOMPARE(Song::compareBy_album(&c, &a), false); //reflexive
}

void TestSong::testCompareBy_genre()
{
    Song a("url", "2", "3", "4", "genre", 1, 1995);
    Song b("url", "2", "3", "4", "ggenre", 1, 1995);
    Song c("url", "2", "3", "4", "genre", 1, 1995);

    //Test 1: a alphabetically before b
    QCOMPARE(Song::compareBy_genre(&a, &b), true); //a.genre is before b.genre
    QCOMPARE(Song::compareBy_genre(&b, &a), false); //check reflexive

    //Test 2: equality => false
    QCOMPARE(Song::compareBy_genre(&a, &c), false); //return false for equality
    QCOMPARE(Song::compareBy_genre(&c, &a), false); //reflexive
}

void TestSong::testCompareBy_trackNum()
{
    Song a("url", "a", "3", "4", "5", 1, 1995);
    Song b("url", "az", "3", "4", "5", 3, 1995);
    Song c("url", "a", "0", "4", "5", 1, 1995);

    //Test 1: a trackNum < b
    QCOMPARE(Song::compareBy_trackNum(&a, &b), true); //a.trackNum < b.trackNum
    QCOMPARE(Song::compareBy_trackNum(&b, &a), false); //check reflexive

    //Test 2: equality => false
    QCOMPARE(Song::compareBy_trackNum(&a, &c), false); //return false for equality
    QCOMPARE(Song::compareBy_trackNum(&c, &a), false); //reflexive
}

void TestSong::testCompareBy_year()
{
    Song a("url", "a", "3", "4", "5", 1, 1995);
    Song b("url", "a", "3", "4", "5", 1, 2100);
    Song c("url", "a", "0", "4", "5", 1, 1995);

    //Test 1: a trackNum < b
    QCOMPARE(Song::compareBy_year(&a, &b), true); //a.year < b.year
    QCOMPARE(Song::compareBy_year(&b, &a), false); //check reflexive

    //Test 2: equality => false
    QCOMPARE(Song::compareBy_year(&a, &c), false); //return false for equality
    QCOMPARE(Song::compareBy_year(&c, &a), false); //reflexive
}

void TestSong::testJson()
{
    Song a("url", "2", "3", "4", "5", 1, 1995);
    std::string repr = a.toString();
    Song copy(repr);
    QCOMPARE(a.Equals(&copy), true);
}
