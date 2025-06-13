#include "mainwindow.h"
#include "common.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    bbb::initializeLocalSession();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
