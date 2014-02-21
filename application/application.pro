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

# Background job related source files
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
    src/QdialogSettings.cpp

# UI related source files
SOURCES += \
    src/QwindowMain.cpp \
    src/QplayerVideo.cpp \
    src/QitemVideo.cpp \
    src/QdialogCalibration.cpp \
    src/QdialogAbout.cpp \
    src/QitemFace.cpp \
    src/QdialogSplit.cpp \
    src/QitemEvent.cpp

# Background job related headers
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
    src/QdialogSettings.hpp

# UI related headers
HEADERS += \
    src/QdialogAbout.hpp \
    src/QitemVideo.hpp \
    src/QdialogSplit.hpp \
    src/QplayerVideo.hpp \
    src/QwindowMain.hpp \
    src/QitemFace.hpp \
    src/QdialogCalibration.hpp \
    src/QitemEvent.hpp

# UI forms
FORMS    += $$files(ui/*.ui)

# Place to pack extra resources
RESOURCES += $$files(resources/*.qrc)
