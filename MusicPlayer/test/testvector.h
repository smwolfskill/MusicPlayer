#ifndef TESTVECTOR_H
#define TESTVECTOR_H

#include <QtTest/QtTest>
#include "vector.h"

/**
 * @brief TestVector --- for testing functionality of Vector class.
 * @author      Scott Wolfskill
 * @created     11/28/2017
 * @last_edit   12/04/2017
 */
class TestVector : public QObject
{
    Q_OBJECT

private:
    Vector<int> * emptyPlaylist;
    Vector<int> * song1Playlist;
    int song1;
    int song2;

private slots:
    // functions executed by QtTest before and after test suite
    /*void initTestCase();
    void cleanupTestCase();*/

    // functions executed by QtTest before and after each test
    void init();
    void cleanup();

    void testContains();
    void testFind();
    void testInsertBefore();
    void testRemoveAt();
    void testSort();
};

#endif // TESTVECTOR_H
