#ifndef COMMON_H
#define COMMON_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QDateTime>

// resource paths
#define QSS_CONSOLE_PATH    ":/styles/resources/qss/console.qss"
#define ICO_MAIN_PATH       ":/icons/resources/icons/bbb.ico"

// string patterns
#define PATTERN_OUT     ">" // all patterns have to be striped
#define PATTERN_IN      "<"
#define PATTERN_VAR     "$"

// environment
#define ENV_JSON        "./executor/data/env.json"  // cannot be relocated
#define ENV_USER        "USER"
#define ENV_PWD         "PWD"
#define ENV_PATH        "PATH"

namespace bbb {

    static QString varPattern = "$";

    inline bool initializeLocalSession() noexcept(false)
    {
        // check pwd directori and init .json configs
        static bool initialized = false;
        if(initialized){return true;}

        QFile data(ENV_JSON);
        data.open(QIODevice::ReadOnly | QIODevice::Text);
        if(!data.isOpen()){
            throw std::runtime_error("failed to initialize local session environment");
        }

        QJsonObject obj = QJsonDocument::fromJson(data.readAll()).object();
        if(obj.isEmpty()){
            throw std::runtime_error("failed to initialize local session environment");
        }
        data.close();

        QString pwd = QDir::currentPath();
        obj.remove(ENV_PWD);    // no reason why without this move it doesn't works
        obj.insert(ENV_PWD, pwd);

        data.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        if(!data.isOpen()){
            throw std::runtime_error("failed to initialize local session environment");
        }

        data.write(QJsonDocument(obj).toJson());
        data.close();

        initialized = true;
        return true;
    }

    inline QString helloBBB()
    {
        QString moment = "Session started at " + QDateTime::currentDateTime().toString() + "\n\n";
        QString intro = "\nBBB-Shell DanilaEfimov (c). All rights reserved\n";
        QString welcome = "Welcome to custom terminal from SSAU.\n";
        return intro + welcome + moment;
    }
}

#endif // COMMON_H
