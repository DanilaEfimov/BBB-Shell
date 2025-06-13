#ifndef ICOMMANDSTRATEGY_H
#define ICOMMANDSTRATEGY_H

#include <QString>
#include <QTextEdit>

class ICommandStrategy
{
public:
    ICommandStrategy() = delete;
    virtual int execute(const QString& command, QTextEdit* console) const = 0;
};

#endif // ICOMMANDSTRATEGY_H
