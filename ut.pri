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
unix: {
    INCLUDEPATH += $$PWD/../gmock-1.6.0/gtest/include
    DEPENDPATH += $$PWD/../gmock-1.6.0/gtest/include

    LIBS += -L$$PWD/../gmock-1.6.0/gmock_build -lgmock

    INCLUDEPATH += $$PWD/../gmock-1.6.0/include
    DEPENDPATH += $$PWD/../gmock-1.6.0/include

    PRE_TARGETDEPS += $$PWD/../gmock-1.6.0/gmock_build/libgmock.a
}
