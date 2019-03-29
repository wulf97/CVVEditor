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
    VideoLoader.cpp \
    VideoSeq.cpp \
    VideoSeqItem.cpp \
    VideoSeqEffects.cpp

HEADERS += \
    Core.h \
    PluginManager.h \
    VideoLoader.h \
    VideoSeq.h \
    VideoSeqItem.h \
    IEffect.h \
    VideoSeqEffects.h

message("Build core")

DISTFILES += \
    ../plugins/plugin_config.pri
