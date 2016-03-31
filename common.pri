#qmake input for common targets

QT_VERSION = 4

QT += core

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += $$PWD/gui \
               $$PWD/main \
               $$PWD/source \
               $$PWD/source/plots \
               $$PWD/source/fft \
               $$PWD/source/dataProviders \
               $$PWD/tests \
               $$PWD/externals


HEADERS += $$PWD/source/fft/Fftw.hpp \
           $$PWD/source/fft/FftwWrapper.hpp \
           $$PWD/source/fft/IFftw.hpp \
           $$PWD/source/plots/BasePlotBuffer.hpp \
           $$PWD/source/plots/AbsBuffer.hpp \
           $$PWD/source/plots/HoldMaxBuffer.hpp \
           $$PWD/source/plots/PhaseBuffer.hpp \
           $$PWD/source/dataProviders/IDataProvider.hpp \
           $$PWD/source/dataProviders/HackRfInterface.hpp \
           $$PWD/source/dataProviders/SamplesAdapter.hpp \
           $$PWD/source/IDataReceiver.hpp \
           $$PWD/source/Types.hpp \
           $$PWD/source/Constants.hpp

SOURCES += $$PWD/source/fft/FftwWrapper.cpp \
           $$PWD/source/plots/BasePlotBuffer.cpp \
           $$PWD/source/plots/AbsBuffer.cpp \
           $$PWD/source/plots/HoldMaxBuffer.cpp \
           $$PWD/source/plots/PhaseBuffer.cpp \
           $$PWD/source/dataProviders/HackRfInterface.cpp \
           $$PWD/source/dataProviders/SamplesAdapter.cpp

# external includes and libraries
INCLUDEPATH += $$PWD/externals/boost_1_57_0/
INCLUDEPATH += $$PWD/externals/qwt-6.1.2/include
INCLUDEPATH += externals/libhackrf/src

LIBS += -lfftw3
LIBS += -Lexternals/qwt-6.1.2/lib -lqwt
LIBS += -Lexternals/libharckrf/lib -lhackrf





