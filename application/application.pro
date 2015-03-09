INCLUDEPATH += . src

# Just to get all the warnings on compilation
WARNINGS += -Wall

# Optimization flags
QMAKE_CXXFLAGS_RELEASE *= -O3

TEMPLATE = app

# The following keeps the generated files separate from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs

# Output binary name
TARGET = BioFoV

# Qt components to be included
QT += core gui
QT += printsupport
QT += widgets

# Translations
TRANSLATIONS = resources/project_pt.ts

# Static link Qt
CONFIG+=static

# Configuration for *ix systems
unix {
	CONFIG += link_pkgconfig
	PKGCONFIG += $$PWD/../third-party/linux-install/lib/pkgconfig/opencv.pc
	PKGCONFIG += $$PWD/../third-party/linux-install/lib/pkgconfig/lib*.pc
}
# Configurations for MS Windows
# Order was copied from the linux pkgconfig
win32 {
	LIBS += -L $$PWD/../third-party/windows-install/x64/mingw/staticlib
	LIBS += -static -lopencv_contrib248 -lopencv_stitching248 -lopencv_nonfree248 -lopencv_superres248 -lopencv_ocl248 -lopencv_objdetect248 -lopencv_ml248 -lopencv_ts248 -lopencv_videostab248 -lopencv_video248 -lopencv_photo248 -lopencv_calib3d248 -lopencv_features2d248 -lopencv_highgui248 -lIlmImf -llibjasper -llibtiff -llibpng -llibjpeg -lopencv_imgproc248 -lopencv_flann248 -lopencv_core248 -lzlib -lmsvfw32 -lwinmm -lavicap32 -lavifil32 -lws2_32 -lsetupapi -lole32 -lgdi32 -lcomctl32 -lstdc++ -lpthread
	INCLUDEPATH += $$PWD/../third-party/opencv/windows-install/include
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
	src/Drawables/drawlength.cpp \
	src/Drawables/drawreproj.cpp \
	src/Drawables/drawwidth.cpp \
	src/Drawables/drawangle.cpp

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
	src/QitemDrawable.cpp \
	src/QitemPlayer.cpp

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
	src/Drawables/drawlength.hpp \
	src/Drawables/drawreproj.hpp \
	src/Drawables/drawwidth.hpp \
	src/Drawables/drawangle.hpp

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
	src/QitemDrawable.hpp \
	src/QitemPlayer.hpp

# UI forms (XML files)
FORMS += $$files(ui/*.ui)

# Resource files.
RESOURCES += $$files(resources/*.qrc)
