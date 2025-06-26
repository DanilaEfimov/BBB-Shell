#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BBB-nano");

    QFile style(":/nano.qss");
    if (style.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(style.readAll());
        qApp->setStyleSheet(styleSheet);
        style.close();
    } else {
        qWarning() << "cannot open nano.qss";
    }

    QIcon ico = QIcon(":/bbb.ico");
    this->setWindowIcon(ico);
}

MainWindow::~MainWindow()
{
    delete ui;
}
