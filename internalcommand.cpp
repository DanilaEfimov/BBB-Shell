#include "internalcommand.h"
#include "console.h"

const QMap<QString, int> InternalCommand::InternalCommands = {
    InternalCommand::KeyOp("clear", bbb::InternalCommandsCodes::clear),
    InternalCommand::KeyOp("whoami", bbb::InternalCommandsCodes::whoami),
    InternalCommand::KeyOp("help", bbb::InternalCommandsCodes::help),
    InternalCommand::KeyOp("pwd", bbb::InternalCommandsCodes::pwd),
    InternalCommand::KeyOp("nano", bbb::InternalCommandsCodes::nano),
    InternalCommand::KeyOp("exit", bbb::InternalCommandsCodes::exit),
};

int InternalCommand::execute(const QStringList &command, Console *console) const
{
    if(command.empty()){
        return -1;
    }

    QString name = command[0];
    int code = this->getCode(name);

    switch(code){
        case bbb::InternalCommandsCodes::clear: this->clear(console);   break;
        case bbb::InternalCommandsCodes::help:  this->help(console);    break;
        case bbb::InternalCommandsCodes::pwd:   this->pwd(console);     break;
        case bbb::InternalCommandsCodes::exit:  this->exit(console);    break;
        case bbb::InternalCommandsCodes::whoami:this->whoami(console);  break;
        case bbb::InternalCommandsCodes::nano:  this->nano(console, command); break;
        default:
            console->errorOccured("Undefined operation name[" + name + "], check all declared symbols");
            console->printPrompt();
    }

    return 0;
}

int InternalCommand::type() const
{
    return internal;
}

bool InternalCommand::isDefinedCommand(const QString name)
{
    return InternalCommands.find(name) != InternalCommands.end();
}

int InternalCommand::getCode(const QString name)
{
    if(isDefinedCommand(name)){
        return InternalCommands[name];
    }
    return -1;
}

void InternalCommand::clear(Console *console) const
{
    console->clear();
    console->printPrompt();
}

void InternalCommand::help(Console *console) const
{
    QString helpMessage =  R"(
        Available commands:

          echo [text]           - Print the specified text to the terminal.
          cd [dir]              - Change the current directory to [dir].
          ls                    - List files and directories in the current directory.
          moduser [options]     - Modify user settings (e.g. permissions, name).
          mkdir [dirname]       - Create a new directory with the given name.
          cat [file]            - Display the contents of a file.
          touch [filename]      - Create an empty file or update its timestamp.
          rm [target]           - Remove a file or directory.
          whoami                - Show the current user name.
          pwd                   - Print the current working directory.
          nano [abs_path]       - Launch the graphical bbb-nano editor (requires absolute path).
          clear                 - Clear the console screen.
          exit                  - Close the shell.

        Type 'help' to print this message.
    )";
    console->outputOccured(helpMessage);
    console->printPrompt();
}

void InternalCommand::pwd(Console *console) const
{
    QString pwd = console->env.getPWD();
    console->outputOccured(pwd);
    console->printPrompt();
}

void InternalCommand::exit(Console *console) const
{
    console->setReadOnly(true);
    emit console->exit();
}

void InternalCommand::whoami(Console *console) const
{
    QString user = console->env.getUSERNAME();
    console->outputOccured(user);
    console->printPrompt();
}

void InternalCommand::nano(Console *console, const QStringList &command) const
{
    if(command.size() == 0){
        return;
    }

    QString nanopath = "./executor/bbb/bbb-nano/bbb_nano.exe";
    console->setReadOnly(true);

    QProcess *plaintexteditor = new QProcess(console);

    connect(plaintexteditor, &QProcess::finished, console, [console, plaintexteditor]() {
        console->setReadOnly(false);
        plaintexteditor->deleteLater();
        console->printPrompt();
    });

    QStringList joined = command;
    joined.pop_front();

    plaintexteditor->start(nanopath, QStringList(joined.join(' ')));
}
