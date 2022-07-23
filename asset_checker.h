#ifndef Asset_CHECKER_H
#define Asset_CHECKER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

#include "downloader.h"
#include "settings.h"
#include "game.h"

class Downloader;

class File
{
public:
    File(QString url, QString path, QString sha1, int status);
    QString url, path;
    QString sha1;
    enum fileStatus
    {
        unexisted = 0,
        unreadable = 1,
        broken = 2,
        fine = 3
    };
    int status;
};

class AssetChecker : public QObject
{
    Q_OBJECT
public:
    explicit AssetChecker(Settings *settings, QObject *parent = nullptr);

    enum fileStatus
    {
        unexisted = 0,
        unreadable = 1,
        broken = 2,
        fine = 3
    };

    int static checkFile(QString path, QString sha1);

    QFile gameFile, gameJsonFile;

    Q_INVOKABLE int checkGame(int index);
    Q_INVOKABLE int checkGameJson(int index);

    QList<File> assetList, libraryList;
    QFile assetJsonFile;
    enum assetStatus
    {
        cannotGetIndex = 4,
        assetUnreadable = 5,
        assetBroken = 6,
        assetFine = 7
    };
    enum libraryStatus
    {
        libraryUnreadable = 8,
        libraryBroken = 9,
        libraryFine = 10
    };
    Q_INVOKABLE int checkAsset(int index);
    Q_INVOKABLE int checkLibrary(int index);
    Q_INVOKABLE int checkNativeLibrary(int index);

    Downloader *downloader;
    Q_INVOKABLE int startDownload();

    Settings *settings;

signals:
};

#endif // Asset_CHECKER_H
