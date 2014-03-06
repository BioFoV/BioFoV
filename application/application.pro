INCLUDEPATH += . src

# Just to get all the warnings on compilation.
WARNINGS += -Wall

TEMPLATE = app

# The following keeps the generated files at least somewhat separate 
# from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs

# Output binary name
TARGET = project

# Qt components to be included
QT += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TRANSLATIONS = resources/project_pt.ts

# Configuration for *ix systems
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

# Configurations for MS Windows
win32 {
    LIBS += -L C:\opencv-2.4.8\build\install\x64\mingw\lib
    LIBS += -lopencv_core248 -lopencv_highgui248 -lopencv_video248 -lz
    LIBS += -lopencv_imgproc248 -lopencv_calib3d248 -lopencv_contrib248 -lopencv_objdetect248
    INCLUDEPATH += C:\opencv-2.4.8\build\install\include
}

# General purpose source files
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
    src/Drawables/drawable.cpp \
    src/player.cpp \
    src/Drawables/drawlength.cpp

# UI related source files
SOURCES += \
    src/QwindowMain.cpp \
    src/QplayerVideo.cpp \
    src/QitemVideo.cpp \
    src/QdialogCalibration.cpp \
    src/QdialogAbout.cpp \
    src/QitemFace.cpp \
    src/QdialogSplit.cpp \
    src/QitemEvent.cpp \
    src/QdialogSettings.cpp \
    src/QtreeFaces.cpp \
    src/QtreeVideos.cpp \
    src/QitemFrame.cpp \
    src/QitemDrawable.cpp

# General purpose headers
HEADERS += \
    src/Event/Event.hpp \
    src/Feature/Feature.hpp \
    src/Frame/Frame.hpp \
    src/Individual/Individual.hpp \
    src/Snapshot/Snapshot.hpp \
    src/Video/Video.hpp \
    src/Video/BackgroundSubtraction.hpp \
    src/player.hpp \
    src/camera.hpp \
    src/Drawables/drawable.hpp \
    src/Drawables/rectanglemask.hpp \
    src/modifier.hpp \
    src/exclusionmod.hpp \
    src/Drawables/drawheight.hpp \
    src/Feature/faces.hpp \
    src/Drawables/drawlength.hpp

# UI related headers
HEADERS += \
    src/QdialogAbout.hpp \
    src/QitemVideo.hpp \
    src/QdialogSplit.hpp \
    src/QplayerVideo.hpp \
    src/QwindowMain.hpp \
    src/QitemFace.hpp \
    src/QdialogCalibration.hpp \
    src/QitemEvent.hpp \
    src/QdialogSettings.hpp \
    src/QtreeFaces.hpp \
    src/QtreeVideos.hpp \
    src/QitemFrame.hpp \
    src/QitemDrawable.hpp

# UI forms (XML files)
FORMS    += $$files(ui/*.ui)

# Resource files.
RESOURCES += $$files(resources/*.qrc)
