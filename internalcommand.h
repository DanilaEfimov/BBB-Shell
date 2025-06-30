#ifndef INTERNALCOMMAND_H
#define INTERNALCOMMAND_H

#include "icommandstrategy.h"
#include <QMap>

namespace bbb {
    enum InternalCommandsCodes {
        exit, clear, help, pwd, whoami, nano
    };
};

class InternalCommand : public ICommandStrategy
{
public:
    using KeyOp = std::pair<QString, int>;

    InternalCommand() = default;
    virtual int execute(const QStringList& command, Console* console) const override;
    virtual int type() const override;

    static bool isDefinedCommand(const QString name);
    static int getCode(const QString name);

private:
    const static QMap<QString, int> InternalCommands;

    void clear(Console* console) const;
    void help(Console* console) const;
    void pwd(Console* console) const;
    void exit(Console* console) const;
    void whoami(Console* console) const;
    void nano(Console* console, const QStringList& command) const;
};

#endif // INTERNALCOMMAND_H
