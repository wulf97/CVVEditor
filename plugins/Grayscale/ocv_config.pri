VERSION_BUILD = 430

unix {
    INCLUDEPATH += /usr/local/include/opencv4
    LIBS += -L/usr/local/lib
    LIBS += -lopencv_core
    LIBS += -lopencv_imgproc
    LIBS += -lopencv_imgcodecs
    LIBS += -lopencv_videoio
}

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
