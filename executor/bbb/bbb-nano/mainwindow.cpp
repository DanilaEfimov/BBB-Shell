#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QKeyEvent>
#include <QMessageBox>

MainWindow::MainWindow(QString filename, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , filename(filename)
{
    ui->setupUi(this);
    this->setWindowTitle("BBB-nano");
    ui->file_name->setText(filename);

    this->setDarkTheme();

    QFile file(filename);

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString all = file.readAll();
        ui->editor->setText(all);
        file.close();
    }
    else{
        QMessageBox::warning(this, "Error", "Failed to open file for reading");
    }

    this->bind();

    QIcon ico(":/bbb.ico");
    this->setWindowIcon(ico);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bind()
{
    connect(ui->dark_theme, &QAction::triggered, this, &MainWindow::setDarkTheme);
    connect(ui->light_theme, &QAction::triggered, this, &MainWindow::setLightTheme);
    connect(ui->align_ev, &QAction::triggered, this, &MainWindow::alignText);
}

void MainWindow::setLightTheme()
{
    QFile style(":/nanoLight.qss");
    if (style.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(style.readAll());
        qApp->setStyleSheet(styleSheet);
        style.close();
    } else {
        qWarning() << "cannot open nanoDark.qss";
    }
}

void MainWindow::setDarkTheme()
{
    QFile style(":/nanoDark.qss");
    if (style.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(style.readAll());
        qApp->setStyleSheet(styleSheet);
        style.close();
    } else {
        qWarning() << "cannot open nanoLight.qss";
    }
}

void MainWindow::alignText()
{
    QStringList lines = ui->editor->toPlainText().split('\n');
    for(auto& line : lines){
        line = line.trimmed();
    }
    ui->editor->setText(lines.join('\n'));
}

void MainWindow::save(const QString &filename)
{
    QFile file(filename);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open file for writing");
        return;
    }

    QString text = ui->editor->toPlainText();
    QTextStream out(&file);
    out << text;

    file.close();
}

void MainWindow::deleteLine()
{
    QTextCursor cursor = ui->editor->textCursor();
    cursor.select(QTextCursor::BlockUnderCursor);
    cursor.removeSelectedText();
    cursor.deleteChar();
}

void MainWindow::exit()
{
    this->close();
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    int key = ev->key();

    if(ev->modifiers() & Qt::ControlModifier){
        switch(key){
        case Qt::Key_S:
            this->save(this->filename);
            break;
        case Qt::Key_R:
            this->exit();
            break;
        case Qt::Key_D:
            this->deleteLine();
            break;
        default:
            break;
        }
    }

    QMainWindow::keyPressEvent(ev);
}
