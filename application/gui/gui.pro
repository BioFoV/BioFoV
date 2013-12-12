#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T14:18:19
#
#-------------------------------------------------

! include( ../common.pri ) {
    error( Could not find the common.pri file! )
}

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

# reset sources
SOURCES += \
    about.cpp \
    mainwindow.cpp \
    videoplayer.cpp \
    videoitem.cpp \
    eventitem.cpp \
    splitdialog.cpp

# reset headers
HEADERS += \
    about.hpp \
    mainwindow.hpp \
    videoplayer.hpp \
    videoitem.hpp \
    eventitem.hpp \
    splitdialog.hpp

FORMS    += $$files(*.ui)

RESOURCES += $$files(*.qrc)

LIBS += -L../framework -lframework
