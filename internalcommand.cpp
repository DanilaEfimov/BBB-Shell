#include "internalcommand.h"
#include "console.h"

const QMap<QString, int> InternalCommand::InternalCommands = {
    InternalCommand::KeyOp("clear", bbb::InternalCommandsCodes::clear),
    InternalCommand::KeyOp("help", bbb::InternalCommandsCodes::help),
    InternalCommand::KeyOp("pwd", bbb::InternalCommandsCodes::pwd),
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
        default:
            console->errorOccured("Undefined operation name[" + name + ", check all declared symbols");
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
    QString helpMessage = "\nclear\t- remove all from colsole\n" \
                        "pwd\t- equals to echo $PWD, print current path\n" \
                        "cd\t- 'Change Directory', change current path\n" \
                        "\nhelp\t- print this message\n";
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
