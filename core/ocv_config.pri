VERSION_BUILD = 343

win32-msvc*{
    INCLUDEPATH += C:/Projects/OpenCV/opencv/build/install/include
    LIBS += -LC:/Projects/OpenCV/opencv/build/install/x64/vc15/lib
    CONFIG(debug, debug|release) {
        LIBS += -lopencv_core$${VERSION_BUILD}d
        LIBS += -lopencv_imgproc$${VERSION_BUILD}d
        LIBS += -lopencv_imgcodecs$${VERSION_BUILD}d
    }

    CONFIG(release, debug|release) {
        LIBS += -lopencv_core$${VERSION_BUILD}
        LIBS += -lopencv_imgproc$${VERSION_BUILD}
        LIBS += -lopencv_imgcodecs$${VERSION_BUILD}
    }
}

unix {
        LIBS += -lopencv_core
        LIBS += -lopencv_imgproc
        LIBS += -lopencv_imgcodecs
}
