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

class Launcher : public QObject
{
    Q_OBJECT
public:
    explicit Launcher(AssetChecker *assetChecker, QObject *parent = nullptr);
    ~Launcher();

    AssetChecker *assetChecker;

    Q_INVOKABLE void uncompressNativeLibraries();

    Q_INVOKABLE void launchGame();
    QString javaPath = "/opt/zing/zing22.05.0.0-3-jdk17.0.3/bin/java";
    QString gamePath = ".minecraft/versions/1.17.1/1.17.1.jar";

    //JVM arguments
    QString HeapDumpPath = "MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump";
    QString mx = "2048m";

    //System arguments DO NOT USE DOUBLE-BYTE ENCODE IN THE PATH
    QString javaLibraryPath = "natives/";
    QString minecraftLauncherBrand = "SMC_Minecrat_Launcher";
    QString minecraftLauncherVersion = "114514";

    //Minecraft arguments
    QString mainClass = "net.minecraft.client.main.Main";
    QString username = "MCredbear";
    QString version = "SMC_Minecrat_Launcher_114514";
    QString gameDir = ".minecraft/";
    QString assetsDir = ".minecraft/assets/";
    QString assetIndex = "1.17";
    QString uuid = "aacf0d304e8f30458b8b120c0dfa1057";
    QString accessToken = "f8720ef157c94ac296bf1935e65781c5";
    QString userType = "mojang";
    QString versionType = "SMC_Minecrat_Launcher_114514";
    QString width = "800";
    QString height = "400";

    QStringList generateArguments();
    QProcess *gameProcess;

signals:

public slots:
    void onNewOutput();
};

#endif // LAUNCHER_H
