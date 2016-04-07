#include "MainWindow.hpp"
#include "Process.hpp"
#include "Constants.hpp"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
#ifdef NO_GUI
    //TODO
    return 0;
#else
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#endif
}
