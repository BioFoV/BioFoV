#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T14:19:51
#
#-------------------------------------------------
! include( ../common.pri ) {
    error( Could not find the common.pri file! )
}

QT       -= gui

TARGET = framework
#TEMPLATE = lib
#CONFIG += staticlib

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

win32 {
    #LIBS += -LC:/qt/OpenCV246_bin/install/lib -llopencv_core246 -llopencv_highgui246
    LIBS += -L C:\FIXME\opencv\build\install\lib
    LIBS += -lopencv_core245 -lopencv_highgui245 -lopencv_video245
    LIBS += -lopencv_imgproc245
    INCLUDEPATH += C:\FIXME\opencv\build\install\include
}

SOURCES += \
    Event/Event.cpp \
    Feature/Feature.cpp \
    Frame/Frame.cpp \
    Individual/Individual.cpp \
    Snapshot/Snapshot.cpp \
    Video/Video.cpp \
    Video/BackgroundSubtraction.cpp \
    camera.cpp \
    rectanglemask.cpp

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
    camera.hpp \
    drawable.hpp \
    rectanglemask.hpp
