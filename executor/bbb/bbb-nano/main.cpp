#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString filename = argv[1];
    MainWindow w(filename);
    w.show();
    /*
    catch(std::exception& e){
        QMessageBox::warning(nullptr, "Error", "Failed to open file for writing");
        return 0;
    }
    */

    return a.exec();
}
