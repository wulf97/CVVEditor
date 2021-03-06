unix {
        CONFIG(debug, debug|release) {
                CONFIG += DebugBuild
                LIBS += -L$${_PRO_FILE_PWD_}/../../debug/
                DESTDIR = $${_PRO_FILE_PWD_}/../../debug/
        } else {
                CONFIG += ReleaseBuild
                LIBS += -L$${_PRO_FILE_PWD_}/../../release/
                DESTDIR = $${_PRO_FILE_PWD_}/../../release/
        }

        CONFIG += staticlib

        RCC_DIR = $${_PRO_FILE_PWD_}/../../build/rcc
        MOC_DIR = $${_PRO_FILE_PWD_}/../../build/moc
        OBJECTS_DIR = $${_PRO_FILE_PWD_}/../../build/obj
        UI_DIR = $${_PRO_FILE_PWD_}/../../build/ui
}

win32{
    CONFIG(debug, debug|release) {
        TARGET_SUFFIX = d
        message(Debug On)
        CONFIG += DebugBuild
    } else:CONFIG(release, debug|release) {
        message(Release On)
        CONFIG += ReleaseBuild
    } else {
        error(Unsupported build)
    }

    BASEDIR = $${IN_PWD}
    DebugBuild {
        DESTDIR = $${_PRO_FILE_PWD_}/../../debug
        BUILDDIR = $${_PRO_FILE_PWD_}/../../trash/build-debug$${TARGET}
    }
    ReleaseBuild {
        DESTDIR = $${_PRO_FILE_PWD_}/../../release
        BUILDDIR = $${_PRO_FILE_PWD_}/../../trash/build-release$${TARGET}
    }
    OBJECTS_DIR = $${BUILDDIR}/obj
    MOC_DIR = $${BUILDDIR}/moc
    UI_DIR = $${BUILDDIR}/ui
    RCC_DIR = $${BUILDDIR}/rcc

    message(BUILDDIR $$BUILDDIR)
    message(BASEDIR $$BASEDIR DESTDIR $$DESTDIR TARGET $$TARGET)
}
