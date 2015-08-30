Release:DESTDIR = $$PWD/bin
Release:OBJECTS_DIR = $$PWD/bin/release
Release:MOC_DIR = $$PWD/bin/release
Release:RCC_DIR = $$PWD/bin/release
Release:UI_DIR = $$PWD/bin/release

Debug:DESTDIR = $$PWD/bin
Debug:OBJECTS_DIR = $$PWD/bin/debug
Debug:MOC_DIR = $$PWD/bin/debug
Debug:RCC_DIR = $$PWD/bin/debug
Debug:UI_DIR = $$PWD/bin/debug

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
