#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    MainWindow(QString filename, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString filename;

    void bind();

private slots:
    void setLightTheme();
    void setDarkTheme();
    void alignText();

    void save(const QString& filename);
    void deleteLine();
    void exit();

protected:
    void keyPressEvent(QKeyEvent* ev) override;
};
#endif // MAINWINDOW_H
