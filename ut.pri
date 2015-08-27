#qmake data for unit tests' targets

INCLUDEPATH += tests

SOURCES += \
    $$PWD/main/mainUt.cpp \
    $$PWD/tests/FftwWrapperTests.cpp \
    $$PWD/tests/FrameAnalyzerTests.cpp \
    $$PWD/tests/PlotInputTests.cpp


HEADERS += \
    $$PWD/tests/FftwWrapperMock.hpp

#google test's libraries
INCLUDEPATH += $$PWD/../../../CppLibs/gmock-1.6.0/gtest/include
DEPENDPATH += $$PWD/../../../CppLibs/gmock-1.6.0/gtest/include

unix|win32: LIBS += -L$$PWD/../../../CppLibs/gmock-1.6.0/ -lgmock

INCLUDEPATH += $$PWD/../../../CppLibs/gmock-1.6.0/include
DEPENDPATH += $$PWD/../../../CppLibs/gmock-1.6.0/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../CppLibs/gmock-1.6.0/gmock.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../../CppLibs/gmock-1.6.0/libgmock.a

