#ifndef INTERNALCOMMAND_H
#define INTERNALCOMMAND_H

#include "icommandstrategy.h"

#include <QMap>

namespace bbb {
    enum InternalCommandsCodes {
        clear,
    };
}

class InternalCommand : public ICommandStrategy
{
    using KeyOp = std::pair<QString, int>;
public:
    InternalCommand() = delete;
    virtual int execute(const QString& command, QTextEdit* console) const override;

private:
    bool isDefinedCommand(QString name) const;
    const QMap<QString, int> InternalCommands{
        KeyOp("clear", bbb::InternalCommandsCodes::clear),
    };
};

#endif // INTERNALCOMMAND_H
