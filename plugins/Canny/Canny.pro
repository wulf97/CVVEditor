include(../plugin_config.pri)

QT += core widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Canny
TEMPLATE = lib
CONFIG += plugin

DEFINES += CANNY_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../../core

SOURCES += \
    src/Canny.cpp

HEADERS += \
    src/Canny.h

FORMS += \
    ui/Canny.ui
