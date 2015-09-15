release: DESTDIR = $$PWD/bin
release: OBJECTS_DIR = $$PWD/bin/release
release: MOC_DIR = $$PWD/bin/release
release: RCC_DIR = $$PWD/bin/release
release: UI_DIR = $$PWD/bin/release

debug: DESTDIR = $$PWD/bin
debug: OBJECTS_DIR = $$PWD/bin/debug
debug: MOC_DIR = $$PWD/bin/debug
debug: RCC_DIR = $$PWD/bin/debug
debug: UI_DIR = $$PWD/bin/debug

include(common.pri)

equals(TARGET, SpectrumAnalyzer) {
    include(app.pri)
}

equals(TARGET, SpectrumAnalyzerUt) {
    include(ut.pri)
}

DISTFILES += common.pri
DISTFILES += app.pri
DISTFILES += ut.pri

win32 {
    QMAKE_CLEAN += $$PWD/bin $$PWD/Makefile*
} else:unix: {
    QMAKE_CLEAN += -r $$PWD/bin $$PWD/Makefile
}


