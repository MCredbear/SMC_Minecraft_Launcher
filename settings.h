#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>

#include "game.h"

/*
{
    "user": {
        "name": "MCredbear",
        "password": "1145141919810",
    },
    "gameList": [
        "1.19": {
            "gameVersion": "1.19",
            "maxMemory": ""
            "jrePath": "jre17/bin/java"
        }
    ]
}
*/


class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    QFile settingsFile;
    QJsonDocument settingsJson;

    Q_PROPERTY (QString account READ getAccount WRITE setAccount NOTIFY onAccountChanged)
    QString account;
    QString getAccount();
    void setAccount(QString account);

    Q_PROPERTY (QString password READ getPassword WRITE setPassword NOTIFY onPasswordChanged)
    QString password;
    QString getPassword();
    void setPassword(QString password);

    QList<Game*> gameList, defaultGameList;

    void readSettingsFile();
    void createNewSettingsFile();
    void saveSettingsFile();
signals:
    void onAccountChanged();
    void onPasswordChanged();
    void onSettingsUnexisted();
    void onSettingsBroken();
    void onSettingsUnreadable();
    void onSettingsUnwriteable();
};

#endif // SETTINGS_H
