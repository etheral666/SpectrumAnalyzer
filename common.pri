#qmake input for common targets

QT_VERSION = 4

QT += core

INCLUDEPATH += $$PWD/gui \
               $$PWD/main \
               $$PWD/source \
               $$PWD/tests \
               $$PWD/externals


HEADERS += $$PWD/source/Fftw.hpp \
           $$PWD/source/FftwWrapper.hpp \
           $$PWD/source/IFftw.hpp \
           $$PWD/source/Types.hpp \
           $$PWD/source/BasePlotBuffer.hpp \
           $$PWD/source/AbsBuffer.hpp \
           $$PWD/source/HoldMaxBuffer.hpp \
           $$PWD/source/PhaseBuffer.hpp \
           $$PWD/source/IDataProvider.hpp \
           $$PWD/source/IDataReceiver.hpp \
           $$PWD/source/Constants.hpp

SOURCES += $$PWD/source/FftwWrapper.cpp \
           $$PWD/source/BasePlotBuffer.cpp \
           $$PWD/source/AbsBuffer.cpp \
           $$PWD/source/HoldMaxBuffer.cpp \
           $$PWD/source/PhaseBuffer.cpp

# external includes and libraries
win32: {
    INCLUDEPATH += $$PWD/../../../CppLibs/fftw-3.3.4/fftw-3.3.4-dll64
    INCLUDEPATH += $$PWD/../../../CppLibs/boost_1_57_0

    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../CppLibs/Qwt-6.1.2/lib/ -lqwt
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../CppLibs/Qwt-6.1.2/lib/ -lqwtd

    INCLUDEPATH += $$PWD/../../../CppLibs/Qwt-6.1.2/include
    DEPENDPATH += $$PWD/../../../CppLibs/Qwt-6.1.2/include
} else:unix: {
    INCLUDEPATH += $$PWD/../boost_1_57_0

    LIBS += -lfftw3
}




