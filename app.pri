#qmake data for QT gui application targets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += main/main.cpp \
    gui/MainWindow.cpp

HEADERS  += gui/MainWindow.hpp

FORMS    += gui/MainWindow.ui

