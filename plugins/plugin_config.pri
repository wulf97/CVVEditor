unix {
        CONFIG(debug, debug|release) {
                CONFIG += DebugBuild
                DESTDIR = $${_PRO_FILE_PWD_}/../../../debug/plugins
        } else {
                CONFIG += ReleaseBuild
                DESTDIR = $${_PRO_FILE_PWD_}/../../../release/plugins
        }

        RCC_DIR = /../../../build/rcc
        MOC_DIR = /../../../build/moc
        OBJECTS_DIR = /../../../build/obj
        UI_DIR = /../../../build/ui
}

#win32 {
#    CONFIG(debug, debug|release) {
#        TARGET_SUFFIX = d
#        message(Debug On)
#        CONFIG += DebugBuild
#    } else:CONFIG(release, debug|release) {
#        message(Release On)
#        CONFIG += ReleaseBuild
#    } else {
#        error(Unsupported build)
#    }

#    BASEDIR = $${IN_PWD}
#    DebugBuild {
#        DESTDIR = $${_PRO_FILE_PWD_}/../../../debug/plugins
#        BUILDDIR = $${_PRO_FILE_PWD_}/../../../trash/build-debug$${TARGET}
#    }
#    ReleaseBuild {
#        DESTDIR = $${_PRO_FILE_PWD_}/../../../release/plugins
#        BUILDDIR = $${_PRO_FILE_PWD_}/../../../trash/build-release$${TARGET}
#    }

#    OBJECTS_DIR = $${BUILDDIR}/obj
#    MOC_DIR = $${BUILDDIR}/moc
#    UI_DIR = $${BUILDDIR}/ui
#    RCC_DIR = $${BUILDDIR}/rcc
#}
