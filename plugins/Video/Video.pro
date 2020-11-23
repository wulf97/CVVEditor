QT += core gui widgets

TEMPLATE = lib
TARGET = VideoNode

CONFIG += plugin

unix {
#DESTDIR = ../../../debug/plugins

CONFIG(debug, debug|release) {
        CONFIG += DebugBuild
        DESTDIR = ../../../debug/plugins
} else {
        CONFIG += ReleaseBuild
        DESTDIR = ../../../release/plugins
}

RCC_DIR = ../../../build/rcc
MOC_DIR = ../../../build/moc
OBJECTS_DIR = ../../../build/obj
UI_DIR = ../../../build/ui

INCLUDEPATH += ../../core
INCLUDEPATH += /usr/local/include/opencv4

LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_videoio
}

HEADERS += \
    CvvINode.h \
    src/CvvINodePort.h \
    src/VideoNode.h \
    src/VideoSettings.h \
    src/RangeSlider.h

SOURCES += \
    src/CvvINodePort.cpp \
    src/VideoNode.cpp \
    src/VideoSettings.cpp \
    src/RangeSlider.cpp

FORMS += \
    ui/VideoSettings.ui
