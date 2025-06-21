#include "console.h"
#include "common.h"
#include "formatmanager.h"
#include "externalcommand.h"
#include "internalcommand.h"

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
        if(input.trimmed() == ""){
            this->printPrompt();
        }
        else if (ExternalCommand::isRunnig()) {
            ExternalCommand::write(input + "\n");
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

    const QString prompt = env.getPWD() + PATTERN_OUT + ' ';
    cursor.insertText(prompt);

    promptPosition = cursor.position();

    cursor.setCharFormat(this->formatManager.inputFormat());
    this->setTextCursor(cursor);
}

QString Console::currentInputLine() const
{
    QString text = this->toPlainText();
    text = text.mid(this->promptPosition);

    QStringList lines = text.split('\n', Qt::SkipEmptyParts);
    if(lines.empty())
        return "";

    return lines.last();
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
    QStringList argv = this->tokenizer.getArgv(command);

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

    // checking for a command strategy patterns
    if(InternalCommand::isDefinedCommand(argv[0])){
        InternalCommand cmd;
        cmd.execute(argv, this);
    }
    else if(ExternalCommand::isDefinedCommand(argv[0])){
        ExternalCommand cmd;
        cmd.execute(argv, this);
    }
    else{
        this->errorOccured("Undefined operation name [" + argv[0] + "], check all declared symbols");
        this->printPrompt();
    }
}

void Console::exit()
{
    this->outputOccured("logout...");
    this->setReadOnly(true);
};

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
    catch(std::logic_error& e){
        this->errorOccured(e.what());
    }
    catch(std::exception& e){
        this->errorOccured(e.what());
    }
}
