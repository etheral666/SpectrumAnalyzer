#qmake input for common targets

QT += core

INCLUDEPATH += $$PWD/gui
INCLUDEPATH += $$PWD/main
INCLUDEPATH += $$PWD/source
INCLUDEPATH += $$PWD/tests
INCLUDEPATH += $$PWD/externals


HEADERS += $$PWD/source/FrameAnalyzer.hpp
HEADERS += $$PWD/source/Fftw.hpp
HEADERS += $$PWD/source/FftwWrapper.hpp
HEADERS += $$PWD/source/IFftw.hpp
HEADERS += $$PWD/source/PlotInput.hpp

SOURCES += $$PWD/source/FrameAnalyzer.cpp
SOURCES += $$PWD/source/FftwWrapper.cpp
SOURCES += $$PWD/source/PlotInput.cpp

# external includes and libraries
win32: {
    INCLUDEPATH += $$PWD/../../../CppLibs/fftw-3.3.4/fftw-3.3.4-dll64
    INCLUDEPATH += $$PWD/../../../CppLibs/boost_1_57_0

    LIBS += -L$$PWD/../../../CppLibs/fftw-3.3.4/fftw-3.3.4-dll64 -lfftw3-3
} else:unix:{
    INCLUDEPATH += $$PWD/../boost_1_57_0

    LIBS += -lfftw3
}