#ifndef ICOMMANDSTRATEGY_H
#define ICOMMANDSTRATEGY_H

#include <QString>
#include <QTextEdit>
#include <QObject>

enum {
    internal = 1, external
};

class Console;

class ICommandStrategy : public QObject
{
public:
    ICommandStrategy() = default;
    virtual int execute(const QStringList& command, Console* console) const = 0;
    virtual int type() const = 0;
};

#endif // ICOMMANDSTRATEGY_H
