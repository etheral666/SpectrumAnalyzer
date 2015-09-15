#qmake input for QT gui application targets

QT += widgets
QT += gui

TEMPLATE = app

SOURCES += main/main.cpp \
           gui/MainWindow.cpp

HEADERS += gui/MainWindow.hpp

FORMS   += gui/MainWindow.ui

