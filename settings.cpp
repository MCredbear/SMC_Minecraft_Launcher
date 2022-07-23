#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{
    settingsFile.setFileName("settings.json");
    Game *game_1_19 = new Game("1.19", "2048m", "854", "480", "c0898ec7c6a5a2eaa317770203a1554260699994", "a864e1c23b4bc52c4357505ccc87bb4b1c0455d6");
    Game *game_1_18_2_mod = new Game("1.18.2-mod", "4096m", "854", "480", "2e9a3e3107cca00d6bc9c97bf7d149cae163ef21", "fc60987a89922a2650b25c7c68cfe18b7aea578f");
    defaultGameList.append(game_1_19);
    defaultGameList.append(game_1_18_2_mod);
    gameList = defaultGameList;
    readSettingsFile();
}

QString Settings::getAccount()
{
    return account;
}

void Settings::setAccount(QString account)
{
    this->account = account;
    emit onAccountChanged();
}

QString Settings::getPassword()
{
    return password;
}

void Settings::setPassword(QString password)
{
    this->password = password;
    emit onPasswordChanged();
}

void Settings::readSettingsFile()
{
    if (!settingsFile.exists())
    {
        createNewSettingsFile();
        emit onSettingsUnexisted();
    }
    else
    {
        if (!settingsFile.open(QIODevice::ReadOnly))
        {
            emit onSettingsUnreadable();
        }
        else
        {
            QByteArray jsonData = settingsFile.readAll();
            settingsFile.close();
            QJsonParseError jsonError;
            settingsJson = QJsonDocument::fromJson(jsonData, &jsonError);
            if (jsonError.error != QJsonParseError::NoError)
            {
                if (!settingsFile.open(QIODevice::WriteOnly))
                {
                    emit onSettingsUnwriteable();
                }
                else
                {
                    createNewSettingsFile();
                    emit onSettingsBroken();
                }
            }
            else
            {
                if (settingsJson.object()["user"].isNull())
                {
                    createNewSettingsFile();
                    emit onSettingsBroken();
                }
                else
                {
                    if (settingsJson.object()["user"].toObject()["name"].isNull() | settingsJson.object()["user"].toObject()["password"].isNull())
                    {
                        createNewSettingsFile();
                        emit onSettingsBroken();
                        return;
                    }
                    else {
                        account = settingsJson.object()["user"].toObject()["name"].toString();
                        password = settingsJson.object()["user"].toObject()["password"].toString();
                    }
                    if (!settingsJson.object()["gameList"].isNull())
                    {
                        for (int i = 0; i < settingsJson.object()["gameList"].toArray().count(); i++)
                        {
                            for (int j = 0; j < gameList.count(); j++)
                            {
                                if (gameList.at(j)->version == settingsJson.object()["gameList"].toArray().at(i).toObject()["gameVersion"].toString())
                                {
                                    gameList.at(j)->setMaxMemory(settingsJson.object()["gameList"].toArray().at(i).toObject()["maxMemory"].toString());
                                    gameList.at(j)->setWidth(settingsJson.object()["gameList"].toArray().at(i).toObject()["width"].toString());
                                    gameList.at(j)->setHeight(settingsJson.object()["gameList"].toArray().at(i).toObject()["height"].toString());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Settings::createNewSettingsFile()
{
    settingsFile.open(QIODevice::WriteOnly);
    QJsonObject user;
    user["name"] = "";
    user["password"] = "";
    QJsonArray gameList;
    for (int i = 0; i < Settings::gameList.count(); i++)
    {
        QJsonObject game;
        game["gameVersion"] = Settings::gameList.at(i)->version;
        game["maxMemory"] = Settings::gameList.at(i)->maxMemory;
        game["width"] = Settings::gameList.at(i)->width;
        game["height"] = Settings::gameList.at(i)->height;
        gameList.append(game);
    }
    QJsonObject rootObject;
    rootObject.insert("user", user);
    rootObject.insert("gameList", gameList);
    settingsJson = QJsonDocument();
    settingsJson.setObject(rootObject);
    settingsFile.write(settingsJson.toJson());
    settingsFile.close();
}

void Settings::saveSettingsFile()
{
    if (settingsFile.open(QIODevice::WriteOnly))
    {
        settingsFile.write(settingsJson.toJson());
        settingsFile.close();
    }
    else
    {
        emit onSettingsUnwriteable();
    }
}