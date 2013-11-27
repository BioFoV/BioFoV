#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T14:19:51
#
#-------------------------------------------------

QT       -= gui

TARGET = framework
TEMPLATE = lib
CONFIG += staticlib


#DEFINES += FRAMEWORK_LIBRARY

SOURCES += \
    Event/Event.cpp \
    Feature/Feature.cpp \
    Frame/Frame.cpp \
    Individual/Individual.cpp \
    Snapshot/Snapshot.cpp \
    Video/Video.cpp \
    Video/BackgroundSubtraction.cpp

HEADERS += \
    Event/Event.hpp \
    Feature/Feature.hpp \
    Frame/Frame.hpp \
    Individual/Individual.hpp \
    Snapshot/Snapshot.hpp \
    Video/Video.hpp \
    Video/BackgroundSubtraction.hpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
