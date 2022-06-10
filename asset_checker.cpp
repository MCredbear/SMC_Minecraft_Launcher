#include "asset_checker.h"

AssetChecker::AssetChecker(QObject *parent)
    : QObject{parent}
{
    gameFile.setFileName("./.minecraft/versions/" + GAME_VERSION + "/" + GAME_VERSION + ".jar");
    gameJsonFile.setFileName("./.minecraft/versions/" + GAME_VERSION + "/" + GAME_VERSION + ".json");
}

int AssetChecker::checkGame()
{
    if (gameFile.exists())
    {
        if (gameFile.open(QIODevice::ReadOnly))
        {
            if (QCryptographicHash::hash(gameFile.readAll(), QCryptographicHash::Sha1).toHex() == GAME_HASH)
            {
                gameFile.close();
                return fine;
            }
            else
                return broken;
        }
        else
            return unreadable;
    }
    else
        return unexisted;
}

int AssetChecker::checkGameJson()
{
    if (gameJsonFile.exists())
    {
        if (gameJsonFile.open(QIODevice::ReadOnly))
        {
            if (QCryptographicHash::hash(gameJsonFile.readAll(), QCryptographicHash::Sha1).toHex() == GAME_JSON_HASH)
            {
                gameJsonFile.close();
                return fine;
            }
            else
                return broken;
        }
        else
            return unreadable;
    }
    else
        return unexisted;
}

int AssetChecker::checkAsset()
{
    int checkAssetResult = assetFine;
    int checkGameJsonResult = checkGameJson();
    if (checkGameJsonResult == AssetChecker::fine)
    {
        gameJsonFile.open(QIODevice::ReadOnly);
        QByteArray gameJsonData = gameJsonFile.readAll();
        gameJsonFile.close();
        QJsonParseError jsonError;
        QJsonDocument gameJson = QJsonDocument::fromJson(gameJsonData, &jsonError);
        if (jsonError.error == QJsonParseError::NoError)
        {
            assetJsonFile.setFileName(".minecraft/assets/indexes/" + gameJson.object().value("assetIndex").toObject().value("id").toString() + ".json");
            QString assetJsonSha1 = gameJson.object().value("assetIndex").toObject().value("sha1").toString();
            if (assetJsonFile.exists())
            {
                if (assetJsonFile.open(QIODevice::ReadOnly))
                {
                    QByteArray assetJsonData = assetJsonFile.readAll();
                    assetJsonFile.close();
                    if (QCryptographicHash::hash(assetJsonData, QCryptographicHash::Sha1).toHex() == assetJsonSha1)
                    {
                        for (int i = 0; i < assetJsonData.length(); i++) // This Json file is too large for Qt's Json parser. Although no error parsed after parsing, using QJson*'s functions to this QJsonDocument would crash the program. So I have to read this file in a very original way.
                        {
                            if (assetJsonData.mid(i, 4) == "hash")
                            {
                                fileStatus checkFileResult = checkFile(".minecraft/assets/objects/" + assetJsonData.mid(i + 8, 2) + "/" + assetJsonData.mid(i + 8, 40),
                                                                       assetJsonData.mid(i + 8, 40));
                                assetList.append(File(QString("http://resources.download.minecraft.net/" + assetJsonData.mid(i + 8, 2) + "/" + assetJsonData.mid(i + 8, 40)).replace("http://resources.download.minecraft.net", "https://download.mcbbs.net/assets"),
                                                      QString(".minecraft/assets/objects/" + assetJsonData.mid(i + 8, 2) + "/" + assetJsonData.mid(i + 8, 40)),
                                                      assetJsonData.mid(i + 8, 40),
                                                      checkFileResult));
                                switch (checkFileResult)
                                {
                                case unexisted:
                                    checkAssetResult = assetBroken;
                                    break;
                                case broken:
                                    checkAssetResult = assetBroken;
                                    break;
                                case unreadable:
                                    checkAssetResult = assetUnreadable;
                                    return checkAssetResult;
                                    break;
                                }
                            }
                        }
                        return checkAssetResult;
                    }
                    else
                    { // redownload assetJson
                        QNetworkAccessManager *httpManager = new QNetworkAccessManager();
                        QNetworkRequest getRequest;
                        QNetworkReply *getReply;
                        QEventLoop eventLoop;
                        QObject::connect(httpManager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
                        getRequest.setUrl(gameJson.object().value("assetIndex").toObject().value("url").toString());
                        getRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
                        getReply = httpManager->get(getRequest);
                        eventLoop.exec();
                        if (getReply->error() == QNetworkReply::NoError)
                        {
                            assetJsonFile.open(QIODevice::WriteOnly);
                            assetJsonFile.write(getReply->readAll());
                            assetJsonFile.close();
                            return checkAsset();
                        }
                        else
                            return cannotGetIndex;
                    }
                }
                else
                    return assetUnreadable;
            }
            else
            { // redownload assetJson
                QNetworkAccessManager *httpManager = new QNetworkAccessManager();
                QNetworkRequest getRequest;
                QNetworkReply *getReply;
                QEventLoop eventLoop;
                QObject::connect(httpManager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
                getRequest.setUrl(gameJson.object().value("assetIndex").toObject().value("url").toString());
                getRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
                getReply = httpManager->get(getRequest);
                eventLoop.exec();
                if (getReply->error() == QNetworkReply::NoError)
                {
                    assetJsonFile.open(QIODevice::WriteOnly);
                    assetJsonFile.write(getReply->readAll());
                    assetJsonFile.close();
                    return checkAsset();
                }
                else
                    return cannotGetIndex;
            }
        }
        else
            return broken;
    }
    else
        return checkGameJsonResult;
}

int AssetChecker::checkLibrary()
{
    int checkLibraryResult = libraryFine;
    int checkGameJsonResult = checkGameJson();
    if (checkGameJsonResult == AssetChecker::fine)
    {
        gameJsonFile.open(QIODevice::ReadOnly);
        QByteArray gameJsonData = gameJsonFile.readAll();
        gameJsonFile.close();
        QJsonParseError jsonError;
        QJsonDocument gameJson = QJsonDocument::fromJson(gameJsonData, &jsonError);
        if (jsonError.error == QJsonParseError::NoError)
        {
            for (int i = 0; i < gameJson.object().value("libraries").toArray().count(); i++)
            {
                fileStatus checkFileResult = checkFile(".minecraft/libraries/" + gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("artifact").toObject().value("path").toString(),
                                                       gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("artifact").toObject().value("sha1").toString());

                switch (checkFileResult)
                {
                case unexisted:
                    checkLibraryResult = libraryBroken;
                    break;
                case broken:
                    checkLibraryResult = libraryBroken;
                    break;
                case unreadable:
                    checkLibraryResult = libraryUnreadable;
                    return checkLibraryResult;
                    break;
                }
                libraryList.append(File(gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("artifact").toObject().value("url").toString().replace("https://libraries.minecraft.net", "https://download.mcbbs.net/maven"),
                                        ".minecraft/libraries/" + gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("artifact").toObject().value("path").toString(),
                                        gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("artifact").toObject().value("sha1").toString().toUtf8(),
                                        checkFileResult));
            }
            return checkLibraryResult;
        }
        else
            return broken;
    }
    else
        return checkLibraryResult;
}

AssetChecker::File::File(QString url, QString path, QByteArray sha1, fileStatus status)
{
    this->url = url;
    this->path = path;
    this->sha1 = sha1;
    this->status = status;
}

AssetChecker::fileStatus AssetChecker::checkFile(QString path, QString sha1)
{
    QFile file(path);
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly))
        {
            if (QCryptographicHash::hash(file.readAll(), QCryptographicHash::Sha1).toHex() == sha1)
                return fine;
            else
                return broken;
        }
        else
            return unreadable;
    }
    else
        return unexisted;
}
