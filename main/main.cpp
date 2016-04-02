#include "MainWindow.hpp"
#include "Process.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    Process mainProcess;

    mainProcess.Start();

    return 0;
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
