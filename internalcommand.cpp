#include "internalcommand.h"

int InternalCommand::execute(const QString &command, QTextEdit *console) const
{

}

bool InternalCommand::isDefinedCommand(QString name) const
{
    return this->InternalCommands.find(name) == this->InternalCommands.end();
}
