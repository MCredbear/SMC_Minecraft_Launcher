#include "launcher.h"

Launcher::Launcher(AssetChecker *assetChecker, QObject *parent)
    : QObject{parent}
{
    this->assetChecker = assetChecker;
}

Launcher::~Launcher()
{
    gameProcess->kill();
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

void Launcher::launchGame()
{
    gameProcess = new QProcess();
    connect(gameProcess, &QProcess::readyReadStandardOutput, this, &Launcher::onNewOutput);
    connect(gameProcess, &QProcess::readyReadStandardError, this, &Launcher::onNewOutput);
    gameProcess->start(javaPath, generateArguments());
}

QStringList Launcher::generateArguments()
{
    QStringList arguments;

    // JVM arguments
    arguments << "-XX:HeapDumpPath=" + HeapDumpPath
              << "-Xmx" + mx
              << "-Xmn128m"
              << "-XX:+UnlockExperimentalVMOptions"
              << "-XX:+UseG1GC"
              << "-XX:G1NewSizePercent=20"
              << "-XX:G1ReservePercent=20"
              << "-XX:MaxGCPauseMillis=50"
              << "-XX:G1HeapRegionSize=16m"
              << "-XX:-UseAdaptiveSizePolicy"
              << "-XX:-OmitStackTraceInFastThrow"
              << "-XX:-DontCompileHugeMethods";

    // System arguments DO NOT USE DOUBLE-BYTE ENCODE IN THE PATH
    arguments << "-Djava.library.path=" + javaLibraryPath
              << "-Dminecraft.launcher.brand=" + minecraftLauncherBrand
              << "-Dminecraft.launcher.version=" + minecraftLauncherVersion
              << "-Dminecraft.client.jar=.minecraft/versions/" + GAME_VERSION + "/" + GAME_VERSION + ".jar"
              << "-Dfile.encoding=UTF-8"
              << "-Duser.home=null"
              << "-Dfml.ignoreInvalidMinecraftCertificates=true"
              << "-Dfml.ignorePatchDiscrepancies=true"
              << "-Djava.rmi.server.useCodebaseOnly=true"
              << "-Dcom.sun.jndi.rmi.object.trustURLCodebase=false"
              << "-Dcom.sun.jndi.cosnaming.object.trustURLCodebase=false";

    // class path
    QString classPath;
    QStringList classPathList;
    assetChecker->gameJsonFile.open(QIODevice::ReadOnly);
    QByteArray gameJsonData = assetChecker->gameJsonFile.readAll();
    assetChecker->gameJsonFile.close();
    QJsonDocument gameJson = QJsonDocument::fromJson(gameJsonData);
    for (int i = 0; i < gameJson.object().value("libraries").toArray().count(); i++)
    {
        if (!gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().contains("classifiers"))
            classPathList.append(".minecraft/libraries/" + gameJson.object().value("libraries").toArray().at(i).toObject().value("downloads").toObject().value("artifact").toObject().value("path").toString());
    }
    for (int i = 0; i < classPathList.length(); i++)
    {
#ifdef Q_OS_LINUX
        if (classPathList.at(i).contains("3.2.1"))
            classPathList.removeAt(i);
#endif
#ifdef Q_OS_WINDOWS
        if (classPathList.at(i).contains("3.2.1"))
            classPathList.removeAt(i);
#endif
#ifdef Q_OS_OSX
        if (classPathList.at(i).contains("3.3.2"))
            classPathList.removeAt(i);
#endif
    }
    classPathList.append(".minecraft/versions/1.17.1/1.17.1.jar");
    classPath = classPathList.join(":");
    arguments << "-cp" << classPath;

    // Minecraft arguments
    arguments << mainClass
              << "--username" << username
              << "--version" << version
              << "--gameDir" << gameDir
              << "--assetsDir" << assetsDir
              << "--assetIndex" << assetIndex
              << "--uuid" << uuid
              << "--accessToken" << accessToken
              << "--userType" << userType
              << "--versionType" << versionType;
    return arguments;
}

void Launcher::onNewOutput()
{
    qDebug() << gameProcess->readAll();
}