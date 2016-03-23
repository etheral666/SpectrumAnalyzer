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
           $$PWD/source/Constants.hpp \
           $$PWD/source/HackRfInterface.hpp

SOURCES += $$PWD/source/FftwWrapper.cpp \
           $$PWD/source/BasePlotBuffer.cpp \
           $$PWD/source/AbsBuffer.cpp \
           $$PWD/source/HoldMaxBuffer.cpp \
           $$PWD/source/PhaseBuffer.cpp \
           $$PWD/source/HackRfInterface.cpp

# external includes and libraries
INCLUDEPATH += $$PWD/externals/boost_1_57_0/
INCLUDEPATH += $$PWD/externals/qwt-6.1.2/include
INCLUDEPATH += $$PWD/externals/libhackrf/src

LIBS += -lfftw3
LIBS += -L./externalsqwt-6.1.2/lib -lqwt
LIBS += -L./externals/libharckrf/lib -lhackrf





