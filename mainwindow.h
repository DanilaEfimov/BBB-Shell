#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "console.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDefaultSize();

private:
    Ui::MainWindow *ui;
    QString errorString;

    void setStyle();

signals:
    void errorOccurred(const QString &message);

private slots:
    void handleError(const QString &message);
};
#endif // MAINWINDOW_H
