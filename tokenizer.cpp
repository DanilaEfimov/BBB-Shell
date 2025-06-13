#include "tokenizer.h"
#include "common.h"

QStringList Tokenizer::replaceVars(const QString &line, Environment *env)
{
    QStringList words = line.split(' ', Qt::SkipEmptyParts);

    for(auto& word : words){
        while(word.contains(PATTERN_VAR)){
            // in this scope will not able place empty string

            size_t left = word.indexOf(PATTERN_VAR);
            size_t right = word.size();

            QString var = word.mid(left, right);
            QString val = env->operator[](var.trimmed());
            word.replace(var, val);
        }
    }

    return words;
}
