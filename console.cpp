#include "console.h"
#include "common.h"
#include "formatmanager.h"

#include <QDir>
#include <QKeyEvent>
#include <QScrollBar>
#include <QProcess>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

Console::Console(QWidget* parent, Tokenizer tokenizer, FormatManager formatManager)
    : QTextEdit(parent)
{
    setCursorWidth(2);
    setUndoRedoEnabled(false);
    setContextMenuPolicy(Qt::NoContextMenu);
    connect(this, &QTextEdit::cursorPositionChanged, this, [this](){
        this->moveCursor(QTextCursor::End);
    });

    this->env = InternalEnvironment();
    this->updateEnvironment();
    this->tokenizer = tokenizer;
    this->formatManager = formatManager;

    this->executor = nullptr;
    this->setDefaultSize();
    this->append(bbb::helloBBB());
    printPrompt();
}

void Console::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if (key == Qt::Key_Backspace || key == Qt::Key_Left || key == Qt::Key_Up) {
        if (textCursor().position() <= promptPosition){
            QTextCursor cursor = this->textCursor();
            cursor.setCharFormat(this->formatManager.inputFormat());
            this->setTextCursor(cursor);
            return;
        }
    }

    if (key == Qt::Key_Return || key == Qt::Key_Enter) {
        QTextEdit::keyPressEvent(event);

        QString input = this->currentInputLine();
        if (this->executor && this->executor->state() == QProcess::Running) {
            executor->write(input.toUtf8());
        }
        else{
            emit this->commandEntered(input);
        }

        this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
        return;
    }

    if(event->modifiers() == Qt::ControlModifier && key == Qt::Key_A){
        return; // ignore total selecting
    }

    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
    QTextEdit::keyPressEvent(event);
}

void Console::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}

void Console::printPrompt()
{
    QTextCursor cursor = this->textCursor();
    cursor.movePosition(QTextCursor::End);

    cursor.setCharFormat(this->formatManager.promptFormat());

    const QString prompt = env.username + ' ' + env.pwd + PATTERN_OUT + ' ';
    cursor.insertText(prompt);

    promptPosition = cursor.position();

    cursor.setCharFormat(this->formatManager.inputFormat());
    this->setTextCursor(cursor);
}

QString Console::currentInputLine() const
{
    QString text = this->toPlainText();
    return text.mid(this->promptPosition);
}

void Console::setDefaultSize()
{
    int charWidth = fontMetrics().horizontalAdvance('W');
    int charHeight = fontMetrics().height();

    int width = charWidth * 80 + 10;
    int height = charHeight * 25 + 10;

    this->resize(width, height);
}

void Console::commandEntered(const QString &command)
{
    QStringList argv = command.split(' ', Qt::SkipEmptyParts);

    try{
        argv = this->tokenizer.replaceVars(command, &this->env);
    }
    catch(std::invalid_argument& e){
        this->errorOccured(e.what());
        this->printPrompt();
        return;
    }

    if (argv.isEmpty())
        return;

    argv.insert(0, "main.py");

    this->executor = new QProcess(this);

    connect(this->executor, &QProcess::readyReadStandardOutput, this, [this]() {
        QString output = this->executor->readAllStandardOutput().trimmed();
        if (!output.isEmpty()) {
            this->outputOccured(output);
        }
    });

    connect(this->executor, &QProcess::readyReadStandardError, this, [this]() {
        QString msg = this->executor->readAllStandardError().trimmed();
        if (!msg.isEmpty()) {
            this->errorOccured(msg);
        }
    });

    connect(this->executor, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this](int exitCode, QProcess::ExitStatus status) {
                Q_UNUSED(exitCode);
                Q_UNUSED(status);

                this->printPrompt();
                this->setReadOnly(false);

                this->executor->deleteLater();
                this->executor = nullptr;
            });

    executor->start("python", argv);
}

void Console::errorOccured(const QString &message)
{
    QTextCursor cursor = this->textCursor();
    cursor.movePosition(QTextCursor::End);

    cursor.setCharFormat(this->formatManager.errorFormat());
    cursor.insertText(message + '\n');

    promptPosition = cursor.position();
    cursor.setCharFormat(this->formatManager.inputFormat());

    this->setTextCursor(cursor);
}

void Console::outputOccured(const QString &output)
{
    QTextCursor cursor = this->textCursor();
    cursor.movePosition(QTextCursor::End);

    cursor.setCharFormat(this->formatManager.outputFormat());
    cursor.insertText(output + '\n');

    promptPosition = cursor.position();
    cursor.setCharFormat(this->formatManager.inputFormat());

    this->setTextCursor(cursor);
}

void Console::updateEnvironment()
{
    QFile environment(ENV_JSON);
    environment.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!environment.isOpen()){
        this->errorOccured("Failed to open global environment .json file");
        return;
    }

    QByteArray data = environment.readAll();
    if(data.isNull()){
        this->errorOccured("Failed to parse global environment .json file");
        return;
    }
    environment.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject env = doc.object();

    try{
        this->env.init(env);
    }
    catch(std::logic_error e){
        this->errorOccured(e.what());
    }
}
