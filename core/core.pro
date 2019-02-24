include(../ocv_config.pri)
include(../general_config.pri)

QT += gui

TARGET = core
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Core.cpp \
    PluginManager.cpp \
    VideoLoader.cpp

HEADERS += \
    Core.h \
    PluginManager.h \
    VideoLoader.h

message("Build core")
