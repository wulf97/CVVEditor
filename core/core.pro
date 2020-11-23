include(../ocv_config.pri)
include(../general_config.pri)

QT += gui widgets

TARGET = core
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Core.cpp \
    CvvINodePort.cpp \
    NodeControl.cpp

HEADERS += \
    Core.h \
    CvvINode.h \
    CvvINodePort.h \
    NodeControl.h

message("Build core")

#DISTFILES += \
#    ../plugins/plugin_config.pri
