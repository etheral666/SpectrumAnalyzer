#qmake input for QT gui application targets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += gui

TEMPLATE = app

SOURCES += main/main.cpp
SOURCES +=  gui/MainWindow.cpp
SOURCES +=  externals/qcustomplot.cpp

HEADERS += gui/MainWindow.hpp
HEADERS += externals/qcustomplot.h

FORMS   += gui/MainWindow.ui

