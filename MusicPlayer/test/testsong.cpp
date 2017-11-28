#include "testsong.h"
#include "song.h"


void TestSong::testEquals()
{
    Song a("1", "2", "3", "4", "5", 1995);
    Song b("1", "2", "3", "4", "5", 1995);
    Song c("1", "2", "0", "4", "5", 1995);
    //Test 1: assert reflexive + correct result when actually equal
    QCOMPARE(a.Equals(&b), true);
    QCOMPARE(b.Equals(&a), true);

    //Test 2: assert reflexive + correct result when actually unequal
    QCOMPARE(b.Equals(&c), false);
    QCOMPARE(c.Equals(&b), false);
}

void TestSong::testJson()
{
    Song a("1", "2", "3", "4", "5", 1995);
    std::string repr = a.toString();
    Song copy(repr);
    QCOMPARE(a.Equals(&copy), true);
}
