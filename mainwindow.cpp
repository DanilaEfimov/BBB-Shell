#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include "console.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::errorOccurred, this, &MainWindow::handleError);

    this->console = new Console(this);
    this->setCentralWidget(console);
    connect(this->console, &Console::exit, this, &MainWindow::terminate);

    this->setWindowTitle("BBB-Shell");
    this->setWindowIcon(QIcon(ICO_MAIN_PATH));

    this->setDefaultSize();
    this->setStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDefaultSize()
{
    int charWidth = fontMetrics().horizontalAdvance('W');
    int charHeight = fontMetrics().height();

    int width = charWidth * 80 + 10;
    int height = charHeight * 25 + 10;

    this->resize(width, height);
}

void MainWindow::setStyle()
{
    QFile table(QSS_CONSOLE_PATH);
    table.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!table.isOpen()){
        this->errorString = "failed to set style for console";
        emit this->errorOccurred(this->errorString);
        return;
    }

    QString style = table.readAll();
    this->setStyleSheet(style);

    table.close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}

void MainWindow::handleError(const QString &message)
{
    this->console->errorOccured(message);
}

void MainWindow::terminate()
{
    this->close();
}
