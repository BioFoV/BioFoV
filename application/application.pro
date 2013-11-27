#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T14:18:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = application
TEMPLATE = app

SOURCES += $$files(*.cpp)

HEADERS  += \
    about.hpp \
    mainwindow.hpp

FORMS    += $$files(*.ui)

RESOURCES += $$files(*.qrc)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-framework-Desktop_Qt_5_1_0_GCC_64bit-Debug/release/ -lframework
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-framework-Desktop_Qt_5_1_0_GCC_64bit-Debug/debug/ -lframework
else:unix: LIBS += -L$$PWD/../build-framework-Desktop_Qt_5_1_0_GCC_64bit-Debug/ -lframework

INCLUDEPATH += $$PWD/../build-framework-Desktop_Qt_5_1_0_GCC_64bit-Debug
DEPENDPATH += $$PWD/../build-framework-Desktop_Qt_5_1_0_GCC_64bit-Debug

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-framework-Desktop_Qt_5_1_0_GCC_64bit-Debug/release/framework.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-framework-Desktop_Qt_5_1_0_GCC_64bit-Debug/debug/framework.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-framework-Desktop_Qt_5_1_0_GCC_64bit-Debug/libframework.a
