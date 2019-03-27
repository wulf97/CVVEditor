include(../ocv_config.pri)
include(../general_config.pri)

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

VPATH = ./src
INCLUDEPATH += \
    ../core \
    ./src

unix {
    QMAKE_LFLAGS += -no-pie
    LIBS += -lcore
}

win32 {
    win32-g++{
        LIBS += \
            $${DESTDIR}/libcore.a
    }

    win32-msvc*{
        LIBS += \
            $${DESTDIR}/core.lib \
    }
}

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/PluginList.cpp \
    src/Viewport.cpp \
    src/VideoControlBar.cpp \
    src/VideoCutterList.cpp \
    src/VideoCutter.cpp \
    src/GUIManager.cpp \
    src/RangeSlider.cpp \
    src/EffectRangeList.cpp \
    src/EffectRange.cpp \
    src/EffectList.cpp \
    src/Effect.cpp \
    src/EffectSettings.cpp

HEADERS += \
    src/MainWindow.h \
    src/PluginList.h \
    src/Viewport.h \
    src/VideoControlBar.h \
    src/VideoCutterList.h \
    src/VideoCutter.h \
    src/GUIManager.h \
    src/RangeSlider.h \
    src/EffectRangeList.h \
    src/EffectRange.h \
    src/EffectList.h \
    src/Effect.h \
    src/EffectSettings.h

FORMS += \
    ui/MainWindow.ui \
    ui/PluginList.ui \
    ui/Viewport.ui \
    ui/VideoControlBar.ui \
    ui/VideoCutterList.ui \
    ui/VideoCutter.ui \
    ui/EffectRange.ui \
    ui/EffectList.ui \
    ui/Effect.ui \
    ui/EffectSettings.ui

RESOURCES += \
    ../res.qrc

#----------------------------------------------------------------
#VERSION_BUILD = 343
VERSION_BUILD = 345

win32-msvc*{
    #INCLUDEPATH += C:/Projects/OpenCV/opencv/build/install/include
    INCLUDEPATH += C:/opencv/mybuild/install/include
    LIBS += -LC:/opencv/mybuild/install/x64/vc15/lib
    CONFIG(debug, debug|release) {
        LIBS += -lopencv_core$${VERSION_BUILD}d
        LIBS += -lopencv_imgproc$${VERSION_BUILD}d
        LIBS += -lopencv_imgcodecs$${VERSION_BUILD}d
        LIBS += -lopencv_videoio$${VERSION_BUILD}d
    }

    CONFIG(release, debug|release) {
        LIBS += -lopencv_core$${VERSION_BUILD}
        LIBS += -lopencv_imgproc$${VERSION_BUILD}
        LIBS += -lopencv_imgcodecs$${VERSION_BUILD}
        LIBS += -lopencv_videoio$${VERSION_BUILD}
    }
}

unix {
        LIBS += -L"/usr/local/lib"
        LIBS += -lopencv_core
        LIBS += -lopencv_imgproc
        LIBS += -lopencv_imgcodecs
        LIBS += -lopencv_videoio
}

