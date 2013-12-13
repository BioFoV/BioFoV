TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp

win32 {
    LIBS += -L..\framework\release -L..\gui\release -lframework -lgui
    INCLUDEPATH += C:\FIXME\opencv\build\install\include
}

unix {
    LIBS += -L../framework -L../gui -lframework -lgui

}

# Will build the final executable in the main project directory.
TARGET = ../project
