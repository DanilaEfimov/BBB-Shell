#ifndef CONSOLE_H
#define CONSOLE_H

#include "formatmanager.h"
#include "internalenvironment.h"
#include "tokenizer.h"

#include <QTextEdit>
#include <QProcess>

class Console : public QTextEdit
{
    Q_OBJECT

    friend class InternalCommand;
    friend class ExternalCommand; // for occuring errors, outputs...
public:
    explicit Console(QWidget* parent = nullptr,
                    Tokenizer tokenizer = Tokenizer(),
                    FormatManager formatManager = FormatManager());

    void setDefaultSize();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    void printPrompt();
    QString currentInputLine() const;
    int promptPosition = 0;

    InternalEnvironment env;
    Tokenizer tokenizer;
    FormatManager formatManager;

signals:
    void commandEntered(const QString &command);
    void exit();

public slots:
    void errorOccured(const QString& message);
    void outputOccured(const QString& output);
    void updateEnvironment();

};

#endif // CONSOLE_H
