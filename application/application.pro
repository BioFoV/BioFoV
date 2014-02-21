INCLUDEPATH += . src
WARNINGS += -Wall

TEMPLATE = app

# The following keeps the generated files at least somewhat separate 
# from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs

TARGET = project

QT += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

win32 {
    #LIBS += -LC:/qt/OpenCV246_bin/install/lib -llopencv_core246 -llopencv_highgui246
    LIBS += -L C:\FIXME\opencv\build\install\lib
    LIBS += -lopencv_core245 -lopencv_highgui245 -lopencv_video245
    LIBS += -lopencv_imgproc245
    INCLUDEPATH += C:\FIXME\opencv\build\install\include
}

SOURCES += \
    src/main.cpp \
    src/Event/Event.cpp \
    src/Feature/Feature.cpp \
    src/Frame/Frame.cpp \
    src/Individual/Individual.cpp \
    src/Snapshot/Snapshot.cpp \
    src/Video/Video.cpp \
    src/Video/BackgroundSubtraction.cpp \
    src/camera.cpp \
    src/Drawables/rectanglemask.cpp \
    src/exclusionmod.cpp \
    src/Drawables/drawheight.cpp \
    src/Feature/faces.cpp \
    src/about.cpp \
    src/mainwindow.cpp \
    src/videoplayer.cpp \
    src/videoitem.cpp \
    src/eventitem.cpp \
    src/splitdialog.cpp \
    src/calibrationdialog.cpp \
    src/faceitem.cpp

HEADERS += \
    src/Event/Event.hpp \
    src/Feature/Feature.hpp \
    src/Frame/Frame.hpp \
    src/Individual/Individual.hpp \
    src/Snapshot/Snapshot.hpp \
    src/Video/Video.hpp \
    src/Video/BackgroundSubtraction.hpp \
    src/Event/Event.hpp \
    src/player.hpp \
    src/camera.hpp \
    src/Drawables/drawable.hpp \
    src/Drawables/rectanglemask.hpp \
    src/modifier.hpp \
    src/exclusionmod.hpp \
    src/Drawables/drawheight.hpp \
    src/Feature/faces.hpp \
    src/about.hpp \
    src/mainwindow.hpp \
    src/videoplayer.hpp \
    src/videoitem.hpp \
    src/eventitem.hpp \
    src/splitdialog.hpp \
    src/calibrationdialog.hpp \
    src/faceitem.hpp

FORMS    += $$files(ui/*.ui)

RESOURCES += $$files(resources/*.qrc)
