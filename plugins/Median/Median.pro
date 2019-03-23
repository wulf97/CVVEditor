include(../plugin_config.pri)

QT += core widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Median
TEMPLATE = lib
CONFIG += plugin

DEFINES += CANNY_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../../core

SOURCES += \
    src/Median.cpp

HEADERS += \
    src/Median.h

FORMS += \
    ui/Median.ui
