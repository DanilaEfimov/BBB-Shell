#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "environment.h"

#include <QStringList>

class Tokenizer
{
public:
    Tokenizer() = default;

    static QStringList replaceVars(const QString& line, Environment* env);
};

#endif // TOKENIZER_H
