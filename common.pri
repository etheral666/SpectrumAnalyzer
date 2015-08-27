#qmake info for common targets

QT       += core gui

INCLUDEPATH += \
    $$PWD/gui \
    $$PWD/main \
    $$PWD/source \
    $$PWD/tests \
    $$PWD/externals


HEADERS += \
    $$PWD/source/FrameAnalyzer.hpp \
    $$PWD/source/Fftw.hpp \
    $$PWD/source/FftwWrapper.hpp \
    $$PWD/source/IFftw.hpp \
    $$PWD/source/PlotInput.hpp

SOURCES += \
    $$PWD/source/FrameAnalyzer.cpp \
    $$PWD/source/FftwWrapper.cpp \
    $$PWD/source/PlotInput.cpp

INCLUDEPATH += D:\CppLibs\fftw-3.3.4\fftw-3.3.4-dll64
INCLUDEPATH += D:\CppLibs\boost_1_57_0

LIBS += -LD:\CppLibs\fftw-3.3.4\fftw-3.3.4-dll64 -lfftw3-3
