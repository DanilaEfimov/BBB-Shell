#ifndef INTERNALENVIRONMENT_H
#define INTERNALENVIRONMENT_H

#include "environment.h"
#include "common.h"

#include <QString>
#include <QDir>
#include <QJsonObject>

struct InternalEnvironment : public Environment {

    InternalEnvironment(): pwd(QDir::currentPath()), username(""), tempVars({}){};

private:
    QString pwd;
    QString username;

    QMap<QString, QString> tempVars;

    bool chgPWD(const QString npwd) noexcept(false)
    {
        if(QDir(npwd).exists()){
            this->pwd = npwd;
            return false;
        }
        throw std::logic_error("failed to init environment variable [PWD]");
    }

    bool chgUSERNAME(const QString& nusername) noexcept(false)
    {
        if(nusername != ""){
            this->username = nusername;
            return true;
        }
        throw std::logic_error("failed to init environment variable [USER]");
    }

public:
    void init(const QJsonObject& env) noexcept(false)
    {
        QString nusername = env.value("USER").toString();
        QString npwd = env.value("PWD").toString();
        this->chgUSERNAME(nusername);
        this->chgPWD(npwd);
    };

    virtual QString operator[](const QString name) noexcept(false) override
    {
        for(const QString& var : this->tempVars){
            if(name == var){
                return this->tempVars[name];
            }
        }

        if(name == static_cast<QString>(PATTERN_VAR) + ENV_PWD){
            return this->pwd;
        }
        else if(name == static_cast<QString>(PATTERN_VAR) + ENV_USER){
            return this->username;
        }
        else{
            throw std::invalid_argument("Cannot find such variable in internal environment ["
                                        + name.toStdString() + "]");
        }
    }

    QString getUSERNAME() const
    {
        return this->username;
    };

    QString getPWD() const
    {
        return this->pwd;
    };
};

#endif // INTERNALENVIRONMENT_H
