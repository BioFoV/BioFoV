#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T14:19:51
#
#-------------------------------------------------
! include( ../common.pri ) {
    error( Could not find the common.pri file! )
}

QT       -= gui

#TARGET = framework
#TEMPLATE = lib
#CONFIG += staticlib

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

DEFINES += FRAMEWORK_LIBRARY

SOURCES += \
    Event/Event.cpp \
    Feature/Feature.cpp \
    Frame/Frame.cpp \
    Individual/Individual.cpp \
    Snapshot/Snapshot.cpp \
    Video/Video.cpp \
    Video/BackgroundSubtraction.cpp \
    camera.cpp

HEADERS += \
    Event/Event.hpp \
    Feature/Feature.hpp \
    Frame/Frame.hpp \
    Individual/Individual.hpp \
    Snapshot/Snapshot.hpp \
    Video/Video.hpp \
    Video/BackgroundSubtraction.hpp \
    Event/Event.hpp \
    player.hpp \
    camera.hpp

#unix:!symbian {
#    maemo5 {
#        target.path = /opt/usr/lib
#    } else {
#        target.path = /usr/lib
#    }
#    INSTALLS += target
#}
