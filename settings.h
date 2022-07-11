#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>

#include "game.h"

/*
{
    "users": "MCredbear",
    "gameList": [
        "1.19": {
            "gameVersion": "1.19",
            "gameHash": "",
            "gameJsonHash": "",
            "background": "",
            "maxMemory": ""
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

    QList<Game*> gameList;

signals:
    void onSettingsBroken();
    void onSettingsUnexisted();
};

#endif // SETTINGS_H
