#include "externalcommand.h"
#include "console.h"

const QMap<QString, int> ExternalCommand::ExternalCommands{
    ExternalCommand::KeyOp("cd", bbb::ExternalCommandsCodes::cd),
    ExternalCommand::KeyOp("echo", bbb::ExternalCommandsCodes::echo),
    ExternalCommand::KeyOp("ls", bbb::ExternalCommandsCodes::ls),
    ExternalCommand::KeyOp("moduser", bbb::ExternalCommandsCodes::moduser),
    ExternalCommand::KeyOp("mkdir", bbb::ExternalCommandsCodes::mkdir),
    ExternalCommand::KeyOp("cat", bbb::ExternalCommandsCodes::cat),
    ExternalCommand::KeyOp("touch", bbb::ExternalCommandsCodes::touch),
    ExternalCommand::KeyOp("rm", bbb::ExternalCommandsCodes::rm),
};
QProcess* ExternalCommand::executor = nullptr;

int ExternalCommand::execute(const QStringList &command, Console *console) const
{
    if(command.empty()){
        return -1;
    }

    QString name = command[0];
    int code = this->getCode(name);
    if(code < 0){
        return code;
    }

    QStringList argv = command;
    argv.insert(0, "main.py");

    ExternalCommand::executor = new QProcess();
    ExternalCommand::connectProcess(console);

    executor->start("python", argv);

    return 0;
}

int ExternalCommand::type() const
{
    return external;
}

bool ExternalCommand::isDefinedCommand(QString name)
{
    return ExternalCommands.find(name) != ExternalCommands.end();
}

int ExternalCommand::getCode(const QString name)
{
    if(isDefinedCommand(name)){
        return ExternalCommands[name];
    }
    return -1;
}

bool ExternalCommand::isRunnig()
{
    return (ExternalCommand::executor && ExternalCommand::executor->state() == QProcess::Running);
}

void ExternalCommand::write(const QString& input)
{
    ExternalCommand::executor->write(input.toUtf8());
}

void ExternalCommand::connectProcess(Console *console)
{
    connect(ExternalCommand::executor, &QProcess::readyReadStandardOutput, console, [console]() {
        QString output = ExternalCommand::executor->readAllStandardOutput().trimmed();
        if (!output.isEmpty()) {
            console->outputOccured(output);
        }
    });

    connect(ExternalCommand::executor, &QProcess::readyReadStandardError, console, [console]() {
        QString msg = ExternalCommand::executor->readAllStandardError().trimmed();
        if (!msg.isEmpty()) {
            console->errorOccured(msg);
        }
    });

    connect(ExternalCommand::executor, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            console, [console](int exitCode, QProcess::ExitStatus status) {
                Q_UNUSED(exitCode);
                Q_UNUSED(status);

                console->updateEnvironment();
                console->printPrompt();
                console->setReadOnly(false);

                ExternalCommand::executor->deleteLater();
                ExternalCommand::executor = nullptr;
            });
}
