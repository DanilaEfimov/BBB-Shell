#ifndef EXTERNALCOMMAND_H
#define EXTERNALCOMMAND_H

#include "icommandstrategy.h"

#include <QObject>
#include <QMap>
#include <QProcess>

namespace bbb {
    enum ExternalCommandsCodes {
        echo = 1, cd, ls, moduser, mkdir, cat
    };
}

class ExternalCommand : public ICommandStrategy
{
    Q_OBJECT
public:
    using KeyOp = std::pair<QString, int>;

    ExternalCommand() = default;

    virtual int execute(const QStringList& command, Console* console) const override;
    virtual int type() const override;

    static bool isDefinedCommand(QString name);
    static int getCode(const QString name);
    static bool isRunnig();
    static void write(const QString& input);

private:
    const static QMap<QString, int> ExternalCommands;

    static QProcess* executor;
    static void connectProcess(Console* console);
};

#endif // EXTERNALCOMMAND_H
