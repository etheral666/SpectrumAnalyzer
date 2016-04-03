release: DESTDIR     = $$PWD/bin
release: OBJECTS_DIR = $$PWD/bin/release
release: MOC_DIR     = $$PWD/bin/release
release: RCC_DIR     = $$PWD/bin/release
release: UI_DIR      = $$PWD/bin/release

debug: DESTDIR     = $$PWD/bin
debug: OBJECTS_DIR = $$PWD/bin/debug
debug: MOC_DIR     = $$PWD/bin/debug
debug: RCC_DIR     = $$PWD/bin/debug
debug: UI_DIR      = $$PWD/bin/debug

include(common.pri)

equals(TARGET, SpectrumAnalyzer) {
    include(app.pri)
}

equals(TARGET, SpectrumAnalyzerUt) {
    include(ut.pri)
}

contains(CONFIG, NO_GUI) {
    DEFINES += NO_GUI
}

DISTFILES += common.pri
DISTFILES += app.pri
DISTFILES += ut.pri

QMAKE_CLEAN += -r $$PWD/bin $$PWD/Makefile



