#qmake input for unit tests

INCLUDEPATH += tests \
               tests/TestTools

SOURCES += $$PWD/main/mainUt.cpp \
           $$PWD/tests/UnitTests/FftwWrapperTests.cpp \
           $$PWD/tests/UnitTests/PhaseBufferTests.cpp \
           $$PWD/tests/UnitTests/HoldMaxBufferTests.cpp \
           $$PWD/tests/UnitTests/AbsBufferTests.cpp \
           $$PWD/tests/UnitTests/BasePlotBufferTests.cpp \
           $$PWD/tests/UnitTests/FakeAntennaTests.cpp \
           $$PWD/tests/TestTools/FakeAntenna.cpp

HEADERS += $$PWD/tests/UnitTests/FftwWrapperMock.hpp \
           $$PWD/tests/TestTools/FakeAntenna.hpp

#google test's libraries
win32: {
    INCLUDEPATH += $$PWD/../../../CppLibs/gmock-1.6.0/gtest/include
    DEPENDPATH += $$PWD/../../../CppLibs/gmock-1.6.0/gtest/include

    LIBS += -L$$PWD/../../../CppLibs/gmock-1.6.0/ -lgmock

    INCLUDEPATH += $$PWD/../../../CppLibs/gmock-1.6.0/include
    DEPENDPATH += $$PWD/../../../CppLibs/gmock-1.6.0/include

    win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../CppLibs/gmock-1.6.0/gmock.lib
    else: PRE_TARGETDEPS += $$PWD/../../../CppLibs/gmock-1.6.0/libgmock.a
} else:unix: {
    INCLUDEPATH += $$PWD/../gmock-1.6.0/gtest/include
    DEPENDPATH += $$PWD/../gmock-1.6.0/gtest/include

    LIBS += -L$$PWD/../gmock-1.6.0/gmock_build -lgmock

    INCLUDEPATH += $$PWD/../gmock-1.6.0/include
    DEPENDPATH += $$PWD/../gmock-1.6.0/include

    PRE_TARGETDEPS += $$PWD/../gmock-1.6.0/gmock_build/libgmock.a
}
