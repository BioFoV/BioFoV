TEMPLATE = app

QT += widgets

SOURCES += main.cpp

LIBS += -L../framework -L../gui -lframework -lgui

# Will build the final executable in the main project directory.
TARGET = ../project
