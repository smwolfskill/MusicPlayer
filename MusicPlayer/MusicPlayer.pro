#-------------------------------------------------
#
# Project created by QtCreator 2017-11-10T14:31:05
#
#-------------------------------------------------

QT       += core
QT       += core gui
QT       += multimedia
QT       += widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        frmmain.cpp \
        song.cpp \
        album.cpp \
        importer.cpp \
        artist.cpp \
        musiclibrary.cpp \
        playlist.cpp \
        engine.cpp \
        metadata.cpp \
    genre.cpp

HEADERS += \
        frmmain.h \
    song.h \
    album.h \
    importer.h \
    artist.h \
    musiclibrary.h \
    playlist.h \
    vector.h \
    engine.h \
    metadata.h \
    genre.h \
    compare.h \
    cvector.h


FORMS += \
        frmmain.ui

test {
    message(Test build)
    QT += testlib
    TARGET = MusicPlayer-Tests

    SOURCES -= main.cpp

    SOURCES += test/main.cpp \
               test/testsong.cpp \
               test/testimporter.cpp \
               test/testplaylist.cpp \
               test/testvector.cpp \
               test/testmusiclibrary.cpp

    HEADERS += test/testsong.h \
               test/testimporter.h \
               test/testplaylist.h \
               test/testvector.h \
               test/testmusiclibrary.h

} else {
    message(Normal build)
}

INCLUDEPATH += \
    /usr/local/include/taglib \

LIBS += \
    -L/usr/local/lib \
    -ltag \
    -lz
