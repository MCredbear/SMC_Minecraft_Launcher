#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>
#include <private/qzipreader_p.h>
#include <private/qzipwriter_p.h>

#include "asset_checker.h"
#include "settings.h"
#include "logger.h"

class Launcher : public QObject
{
    Q_OBJECT
public:
    explicit Launcher(Settings *settings, AssetChecker *assetChecker, QObject *parent = nullptr);
    ~Launcher();

    AssetChecker *assetChecker;
    Settings *settings;

    void login(QString username, QString password); // Get uuid and accessToken

    Q_INVOKABLE void uncompressNativeLibraries(int index);

    Q_INVOKABLE void launchGame(int index);
    QString javaPath = "jre17/bin/java";
    QString gamePath(int index);

    //JVM arguments
    QString HeapDumpPath = "MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump";
    QString mx(int index);

    //System arguments DO NOT USE DOUBLE-BYTE ENCODE IN THE PATH
    QString javaLibraryPath(int index);
    QString minecraftLauncherBrand = "SMC_Minecrat_Launcher";
    QString minecraftLauncherVersion = "114514";

    //Minecraft arguments
    QString mainClass = "net.minecraft.client.main.Main";
    QString username();
    QString version = "SMC_Minecrat_Launcher_114514";
    QString gameDir = ".minecraft/";
    QString assetsDir = ".minecraft/assets/";
    QString assetIndex(int index);
    QString uuid;
    QString accessToken;
    QString userType = "mojang";
    QString versionType = "SMC_Minecrat_Launcher_114514";
    QString width(int index);
    QString height(int index);

    QStringList generateArguments(int index);
    QProcess *gameProcess;

signals:

public slots:
    void onNewOutput();
};

#endif // LAUNCHER_H
