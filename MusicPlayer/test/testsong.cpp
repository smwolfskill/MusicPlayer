#include "testsong.h"
#include "song.h"


void TestSong::testEquals()
{
    Song a("1", "2", "3", "4", "5", 1, 1995);
    Song b("1", "2", "3", "4", "5", 1, 1995);
    Song c("1", "2", "0", "4", "5", 1, 1995);
    //Test 1: assert reflexive + correct result when actually equal
    QCOMPARE(a.Equals(&b), true);
    QCOMPARE(b.Equals(&a), true);

    //Test 2: assert reflexive + correct result when actually unequal
    QCOMPARE(b.Equals(&c), false);
    QCOMPARE(c.Equals(&b), false);
}

void TestSong::testCompareBy_trackNum()
{
    Song a("1", "a", "3", "4", "5", 1, 1995);
    Song b("1", "az", "3", "4", "5", 3, 1995);
    Song c("1", "a", "0", "4", "5", 1, 1995);

    //Test 1: a trackNum < b
    QCOMPARE(Song::compareBy_trackNum(&a, &b), true); //a.trackNum < b.trackNum
    QCOMPARE(Song::compareBy_trackNum(&b, &a), false); //check reflexive

    //Test 2: equality => false
    QCOMPARE(Song::compareBy_trackNum(&a, &c), false); //return false for equality
    QCOMPARE(Song::compareBy_trackNum(&c, &a), false); //reflexive
}

void TestSong::testCompareBy_title()
{
    Song a("1", "a", "3", "4", "5", 1, 1995);
    Song b("1", "az", "3", "4", "5", 1, 1995);
    Song c("1", "a", "0", "4", "5", 1, 1995);

    //Test 1: a alphabetically before b
    QCOMPARE(Song::compareBy_title(&a, &b), true); //a.title is before b.title
    QCOMPARE(Song::compareBy_title(&b, &a), false); //check reflexive

    //Test 2: equality => false
    QCOMPARE(Song::compareBy_title(&a, &c), false); //return false for equality
    QCOMPARE(Song::compareBy_title(&c, &a), false); //reflexive
}

void TestSong::testJson()
{
    Song a("1", "2", "3", "4", "5", 1, 1995);
    std::string repr = a.toString();
    Song copy(repr);
    QCOMPARE(a.Equals(&copy), true);
}
