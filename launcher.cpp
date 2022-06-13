#include "launcher.h"

Launcher::Launcher(AssetChecker *assetChecker, QObject *parent)
    : QObject{parent}
{
    this->assetChecker = assetChecker;
}

void Launcher::uncompressNativeLibraries()
{
#ifdef Q_OS_LINUX
    const QString nativeOS = "natives-linux";
#endif
#ifdef Q_OS_WINDOWS
    const QString nativeOS = "natives-windows";
#endif
#ifdef Q_OS_OSX
    const QString nativeOS = "natives-macos";
#endif

    QDir nativeDir;
    if (!nativeDir.exists("natives/"))
        nativeDir.mkdir("natives/");
    assetChecker->gameJsonFile.open(QIODevice::ReadOnly);
    QByteArray gameJsonData = assetChecker->gameJsonFile.readAll();
    assetChecker->gameJsonFile.close();
    QJsonDocument gameJson = QJsonDocument::fromJson(gameJsonData);
    for (int i = 0; i < gameJson.object().value("libraries").toArray().count(); i++)
    {
        if (gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().contains("classifiers"))
            if (gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("classifiers").toObject().contains(nativeOS))
            {
                QZipReader zipReader(".minecraft/libraries/" + gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("classifiers").toObject().value(nativeOS).toObject().value("path").toString());
                zipReader.extractAll("natives/");
            }
    }
}
