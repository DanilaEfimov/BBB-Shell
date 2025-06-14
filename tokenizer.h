#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "environment.h"

#include <QStringList>

class Tokenizer
{
public:
    Tokenizer() = default;

    static QStringList replaceVars(const QString& line, Environment* env);
    static QStringList getFlags(const QString& command);
    static QStringList getArgv(const QString& command);
private:
    static void trim(QStringList& words);
};

#endif // TOKENIZER_H
