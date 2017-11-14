#ifndef TESTTWO_H
#define TESTTWO_H

#include <QtTest/QtTest>

/**
 * @brief TestSong --- for testing functionality of Song class.
 * @author      Scott Wolfskill
 * @created     11/14/2017
 * @last_edit   11/14/2017
 */
class TestSong : public QObject
{
    Q_OBJECT

private slots:
    // functions executed by QtTest before and after test suite
    /*void initTestCase();
    void cleanupTestCase();

    // functions executed by QtTest before and after each test
    void init();
    void cleanup();*/

    void testEquals();
};


#endif // TESTTWO_H
