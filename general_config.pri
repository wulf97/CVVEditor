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
        MAKEFILE = $${_PRO_FILE_PWD_}/../../build/Makefile
}

win32 {
        CONFIG(debug, debug|release) {
                CONFIG += DebugBuild
                DESTDIR = $${_PRO_FILE_PWD_}/../../debug
        } else {
                CONFIG += ReleaseBuild
                DESTDIR = $${_PRO_FILE_PWD_}/../../release
        }

        CONFIG += staticlib

        RCC_DIR = $${_PRO_FILE_PWD_}/../../build/rcc
        MOC_DIR = $${_PRO_FILE_PWD_}/../../build/moc
        OBJECTS_DIR = $${_PRO_FILE_PWD_}/../../build/obj
        UI_DIR = $${_PRO_FILE_PWD_}/../../build/ui
        MAKEFILE = $${_PRO_FILE_PWD_}/../../build/Makefile
}
