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
    Console *console = nullptr;

    QString errorString;

    void setStyle();

protected:
    void closeEvent(QCloseEvent* event) override;

signals:
    void errorOccurred(const QString &message);

public slots:
    void handleError(const QString &message);
    void terminate();
};
#endif // MAINWINDOW_H
