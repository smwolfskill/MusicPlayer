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

void TestSong::testOperatorLessThan()
{
    Song a("1", "a", "3", "4", "5", 1, 1995);
    Song b("1", "az", "3", "4", "5", 1, 1995);
    Song c("1", "a", "0", "4", "5", 1, 1995);

    //Test 1: a < b
    QCOMPARE(a < b, true); //a.title is before b.title
    QCOMPARE(b < a, false); //check reflexive

    //Test 2: equality => false
    QCOMPARE(a < c, false); //return false for equality
    QCOMPARE(c < a, false); //reflexive
}

void TestSong::testJson()
{
    Song a("1", "2", "3", "4", "5", 1, 1995);
    std::string repr = a.toString();
    Song copy(repr);
    QCOMPARE(a.Equals(&copy), true);
}
