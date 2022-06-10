#ifndef Asset_CHECKER_H
#define Asset_CHECKER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QCryptographicHash>

const QByteArray GAME_VERSION = "1.17.1";
const QByteArray GAME_HASH = "8d9b65467c7913fcf6f5b2e729d44a1e00fde150";
const QByteArray GAME_JSON_HASH = "a769e66272ae058c60c27a11b5adb04d7065884a";

class AssetChecker : public QObject
{
    Q_OBJECT
public:
    explicit AssetChecker(QObject *parent = nullptr);

    enum fileStatus
    {
        unexisted = 0,
        unreadable = 1,
        broken = 2,
        fine = 3
    };

    class File
    {
    public:
        File(QString url, QString path, QByteArray sha1, fileStatus status);
        QString url, path;
        QByteArray sha1;
        fileStatus status;
    };

    fileStatus checkFile(QString path, QByteArray sha1);

    QFile gameFile, gameJsonFile, assetJsonFile;

    Q_INVOKABLE int checkGame();
    Q_INVOKABLE int checkGameJson();

    QList<File> assetList, libraryList;
    enum assetStatus
    {
        cannotGetIndex = 4,
        assetUnreadable = 5,
        assetBroken = 6,
        assetFine = 7
    };
    Q_INVOKABLE int checkAsset();
    Q_INVOKABLE int checkLibrary();

signals:
};

#endif // Asset_CHECKER_H
