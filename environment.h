#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QString>

class Environment
{
public:
    Environment() = default;
    virtual QString operator[](const QString name) noexcept(false) = 0;
};

#endif // ENVIRONMENT_H
