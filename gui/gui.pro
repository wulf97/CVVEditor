include(general_config.pri)

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/PluginList.cpp \
    src/Viewport.cpp \
    src/VideoControlBar.cpp \
    src/VideoCutterList.cpp \
    src/VideoCutter.cpp \
    src/GUIManager.cpp

HEADERS += \
    src/MainWindow.h \
    src/PluginList.h \
    src/Viewport.h \
    src/VideoControlBar.h \
    src/VideoCutterList.h \
    src/VideoCutter.h \
    src/GUIManager.h

FORMS += \
    ui/MainWindow.ui \
    ui/PluginList.ui \
    ui/Viewport.ui \
    ui/VideoControlBar.ui \
    ui/VideoCutterList.ui \
    ui/VideoCutter.ui

DISTFILES += \
    general_config.pri
