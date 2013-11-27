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

#TARGET = gui
#TEMPLATE = app

# reset sources
SOURCES += \
    about.cpp \
    mainwindow.cpp

# reset headers
HEADERS += \
    about.hpp \
    mainwindow.hpp

FORMS    += $$files(*.ui)

RESOURCES += $$files(*.qrc)
