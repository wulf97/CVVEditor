include(../ocv_config.pri)
include(../general_config.pri)

QT += gui widgets

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
    VideoEffectList.cpp \
    VideoEffect.cpp

HEADERS += \
    Core.h \
    PluginManager.h \
    VideoLoader.h \
    VideoSeq.h \
    VideoSeqItem.h \
    IEffect.h \
    VideoEffectList.h \
    VideoEffect.h

message("Build core")

DISTFILES += \
    ../plugins/plugin_config.pri
